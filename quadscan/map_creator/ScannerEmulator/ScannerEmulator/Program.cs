using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace ScannerEmulator
{
    class Program
    {
        static void Main(string[] args)
        {
            string comPort = args[0];
            int baundRate = int.Parse(args[1]);

            SerialPort port = new SerialPort(comPort, baundRate, Parity.None, 8, StopBits.One);
            port.ReadBufferSize = 32;
            port.WriteBufferSize = 32;
            port.Open();

            while (true)
            {
                Console.Write("Enter message: ");
                string str = Console.ReadLine();

                if (str == null)
                    continue;

                if (str == "exit")
                    break;

                byte[] data = str.Split().Select(int.Parse).Select(v => (byte) v).ToArray();

                if (data.Length < 7)
                {
                    Console.WriteLine("Wrong arguments");
                    continue;
                }

                try
                {
                    port.RtsEnable = true;

                    port.Write(data, 0, data.Length);
                    Thread.Sleep(100);

                    port.RtsEnable = false;
                }
                catch (Exception ex)
                {
                    port.RtsEnable = false;
                    Console.WriteLine(ex.Message);
                }
            }

            port.Close();
        }
    }
}
