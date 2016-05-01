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

#define ROLL_MIN 190;
#define PITCH_MIN 190;
#define YAW_MIN 110;
#define COLLECTIVE_MIN 100;
#define THROTTLE_MIN 100;

#define ROLL_NEUTRAL 220;
#define PITCH_NEUTRAL 220;
#define COLLECTIVE_NEUTRAL 180;
#define YAW_NEUTRAL 180;

#define THROTTLE_INITIAL 105;

int throttle_value = THROTTLE_INITIAL;
int roll_value = ROLL_NEUTRAL;
int pitch_value = PITCH_NEUTRAL;
int collective_value = COLLECTIVE_NEUTRAL;
int yaw_value = YAW_NEUTRAL;

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
  while(!Serial.available());
  
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
    case 's':
      throttle_value = THROTTLE_MIN;
      roll_value = ROLL_MIN;
      pitch_value = PITCH_MIN;
      yaw_value = YAW_MIN;
      collective_value = COLLECTIVE_MIN;
      analogWrite(THROTTLE, throttle_value);
      analogWrite(ROLL, roll_value);
      analogWrite(PITCH, pitch_value);
      analogWrite(YAW, yaw_value);
      analogWrite(COLLECTIVE, collective_value);
      analogWrite(FLIGHT_MODE, 190);

      delay(1000);
      
      throttle_value = THROTTLE_INITIAL;
      roll_value = ROLL_NEUTRAL;
      pitch_value = PITCH_NEUTRAL;
      yaw_value = YAW_NEUTRAL;
      collective_value = COLLECTIVE_NEUTRAL;
      
      analogWrite(THROTTLE, throttle_value);
      analogWrite(ROLL, roll_value);
      analogWrite(PITCH, pitch_value);
      analogWrite(YAW, yaw_value);
      analogWrite(COLLECTIVE, collective_value);
      analogWrite(FLIGHT_MODE, 200);
      break;
    case 'q':
      throttle_value = THROTTLE_MIN;
      analogWrite(THROTTLE, throttle_value);
      break;
  }
  
  Serial.println(throttle_value);
  Serial.println(roll_value);
  Serial.println(pitch_value);
  Serial.println(yaw_value);
  Serial.println(collective_value);
}
