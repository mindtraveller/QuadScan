using System;
using System.Collections;
using System.Collections.Generic;
using System.IO.Ports;
using System.Net.Sockets;
using System.Threading;
using UnityEngine;
using UnityEngine.UI;

namespace Assets.MapBuilder
{
    public class MapBuilder : MonoBehaviour
    {
        private Thread _listenerThread;
        private SerialPort _serialPort = null;

        private ulong _counter = 0;
        private Vector3 _previousMousePosition;

        private readonly object _syncMessages = new object();
        private Stack<byte[]> _messages = new Stack<byte[]>();

        private List<string> _statusRep = new List<string>(); 

        public GameObject Settings;
        public InputField ComChannelTextField;
        public InputField BodsTextField;
        public Text ErrorsTextField;

        public GameObject Status;
        public Text StatusTextField;

        public GameObject Scanner;
        public GameObject Map;
        public GameObject Tile;
        public Camera Camera;

        public float MoveSpeed = 5;
        public float RotationSpeed = 10;

        public byte MaxDistance = 150;

        private void Start()
        {
            _previousMousePosition = Input.mousePosition;

            Settings.gameObject.SetActive(true);
            Status.gameObject.SetActive(false);
        }

        public void AcceptSettings()
        {
            try
            {
                string portName = ComChannelTextField.text;
                int baudRate = int.Parse(BodsTextField.text);

                RunListener(portName, baudRate);

                Settings.gameObject.SetActive(false);
                Status.gameObject.SetActive(true);
            }
            catch (Exception ex)
            {
                ErrorsTextField.text = ex.Message;
            }
        }

        private void Update()
        {
            UpdateCameraPosition();
            UpdateCameraRotation();

            byte[] mess = null;

            lock (_syncMessages)
                if (_messages.Count != 0)
                    mess = _messages.Pop();

            if (mess != null)
                ParseMessage(mess);

        }

        private void RunListener(string portName, int baudRate)
        {
            _serialPort = new SerialPort(portName, baudRate, Parity.None, 8, StopBits.One);

            _serialPort.Open();

            _listenerThread = new Thread(Listener);
            _listenerThread.Start();
        }

        private void Listener()
        {
            while (true)
            {
                byte[] mess = new byte[7];

                for (int i = 0; i < 7; i++)
                {
                    int value = _serialPort.ReadByte();
                    if (value < 0)
                    {
                        Debug.LogError("Listener was stopped");
                        return;
                    }

                    mess[i] = (byte) value;
                }

                lock (_syncMessages)
                    _messages.Push(mess);
            }
        }

        private void ParseMessage(byte[] mess)
        {
            Scanner.transform.Translate((sbyte) mess[0], (sbyte) mess[1], (sbyte) mess[2]);

            if (mess[3] <= MaxDistance) AddTile(mess[3], 0); 
            if (mess[4] <= MaxDistance) AddTile(mess[4], 90); 
            if (mess[5] <= MaxDistance) AddTile(mess[5], 180); 
            if (mess[6] <= MaxDistance) AddTile(mess[6], 270);

            if (_statusRep.Count > 5)
                _statusRep.RemoveAt(0);

            _statusRep.Add(string.Format("{0} {1} {2}    {3} {4} {5} {6}\r\n", (sbyte) mess[0], (sbyte) mess[1], (sbyte) mess[2], mess[3], mess[4], mess[5], mess[6]));

            StatusTextField.text = "";
            foreach (string str in _statusRep)
            {
                StatusTextField.text += str;
            }
        }

        private void AddTile(int r, float angel)
        {
            var off = Vector3.forward;
            float scale = (float) (r / 100.0);
            off.Scale(new Vector3(scale, scale, scale));

            var go = (GameObject)GameObject.Instantiate(Tile, new Vector3(0, 0, 0), Quaternion.identity);

            go.name = string.Format("Tile {0}", _counter++);
            go.transform.parent = Map.transform;
            go.transform.position = Scanner.transform.position + off;
            go.transform.RotateAround(Scanner.transform.position, Scanner.transform.up, angel);
        }

        private void UpdateCameraPosition()
        {
            Vector3 offset = new Vector3(0, 0, Input.mouseScrollDelta[1]*Time.deltaTime*MoveSpeed);
            Camera.transform.Translate(offset);

            var dir = Camera.transform.position - Vector3.up;
            dir.Normalize();

            var s = Vector3.Dot(dir, Vector3.up);
            if (s <= 0)
            {
                Camera.transform.position = Vector3.up;
            }
            else
            {
                var scale = Mathf.Clamp(Vector3.Distance(Camera.transform.position, Vector3.up), 0, 50);
                var pos = dir;
                pos.Scale(new Vector3(scale, scale, scale));

                Camera.transform.position = pos + Vector3.up;
            }
        }

        private void UpdateCameraRotation()
        {
            Vector3 currentMousePosition = Input.mousePosition;
            Vector3 offset = currentMousePosition - _previousMousePosition;

            _previousMousePosition = currentMousePosition;

            if (!Input.GetMouseButton(1))
                return;

            offset.Normalize();

            float scale = Time.deltaTime * RotationSpeed;
            offset.Scale(new Vector3(scale, scale, 0));

            Camera.transform.RotateAround(Vector3.up, Vector3.up, offset.x);
            Camera.transform.RotateAround(Vector3.up, Camera.transform.right, offset.y);

            var s = Camera.transform.rotation.eulerAngles.x;
            var r = Mathf.Clamp(s, 5, 85);

            Camera.transform.RotateAround(Vector3.up, Camera.transform.right, r - s);
        }

        private void OnApplicationQuit()
        {
            if (_serialPort != null && _serialPort.IsOpen)
                _serialPort.Close();
        }

        private void OnGUI()
        {
            var style = new GUIStyle {fontSize = 12, contentOffset = new Vector2(5, 5)};

            GUILayout.BeginVertical();

            GUILayout.Label("RED -> X | GREEN -> Y | BLUE -> Z", style);
            GUILayout.Label(string.Format("POS: {0}", Camera.transform.position), style);
            GUILayout.Label(string.Format("ROT: {0}", Camera.transform.rotation.eulerAngles), style);

            GUILayout.EndVertical();
        }
    }
}
