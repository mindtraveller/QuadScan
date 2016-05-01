//[100; 250]
#define THROTTLE 3
//[190; 250]
#define ROLL 5
//[190; 250]
#define PITCH 6
//[110; 250]
#define COLLECTIVE 11
#define FLIGHT_MODE 10
//[110; 250]
#define YAW 9


int throttle_value = 100;
int roll_value = 220;
int pitch_value = 220;
int collective_value = 180;
int yaw_value = 180;

void setup() {  
  pinMode(THROTTLE, OUTPUT);
  pinMode(ROLL, OUTPUT); 
  pinMode(PITCH, OUTPUT);
  pinMode(COLLECTIVE, OUTPUT);
  pinMode(FLIGHT_MODE, OUTPUT);
  pinMode(YAW, OUTPUT);

  analogWrite(FLIGHT_MODE, 200);
  
  Serial.begin(9600);
}

void loop() {
  char value = Serial.read();
  switch(value) {
    case 't':
      throttle_value -= 10;
      analogWrite(THROTTLE, throttle_value);
      break;
    case 'T':
      throttle_value += 10;
      analogWrite(THROTTLE, throttle_value);
      break;
    case 'r':
      roll_value -= 10;
      analogWrite(ROLL, roll_value);
      break;
    case 'R':
      roll_value += 10;
      analogWrite(ROLL, roll_value);
      break;
    case 'p':
      pitch_value -= 10;
      analogWrite(PITCH, pitch_value);
      break;
    case 'P':
      pitch_value += 10;
      analogWrite(PITCH, pitch_value);
      break;
    case 'y':
      yaw_value -= 10;  
      analogWrite(YAW, yaw_value);
      break;
    case 'Y':
      yaw_value += 10;  
      analogWrite(YAW, yaw_value);
      break;
    case 'c':
      collective_value -= 10;  
      analogWrite(COLLECTIVE, collective_value);
      break;
    case 'C':
      collective_value += 10;  
      analogWrite(COLLECTIVE, collective_value);
      break;
  }
  
  Serial.println(throttle_value);
  Serial.println(roll_value);
  Serial.println(pitch_value);
  Serial.println(yaw_value);
  Serial.println(collective_value);
}
