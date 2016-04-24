#define pot A2
#define THROTTLE 3
#define ROLL 5
#define PITCH 6
#define COLLECTIVE 9
#define FLIGHT_MODE 10
#define YAW 11

//map value from [0; 255] range into TROTTLE range
uint8_t trottleMapper(uint8_t value) {
  if (value < 120) return 120;
  return value;
}

uint8_t rollMapper(uint8_t value) {
  if (value < 180) return 180;
  return value;
}

uint8_t pitchMapper(uint8_t value) {
  if (value < 180) return 180;
  return value;
}

uint8_t yawMapper(uint8_t value) {
  if (value < 90) return 90;
  return value;
}


void setup() {
  pinMode(pot, INPUT);
  
  pinMode(THROTTLE, OUTPUT); //throttle
  pinMode(ROLL, OUTPUT); //roll
  pinMode(PITCH, OUTPUT); //pitch
  pinMode(COLLECTIVE, OUTPUT);
  pinMode(FLIGHT_MODE, OUTPUT);
  pinMode(YAW, OUTPUT);
  Serial.begin(9600);

  //just to enable
  analogWrite(COLLECTIVE, 100);
  //it is enough to have one flight mode
  analogWrite(FLIGHT_MODE, 100);
}

void loop() {
  int x = analogRead(pot) / 4;

  Serial.println(x);

  analogWrite(THROTTLE, trottleMapper(x));
  analogWrite(ROLL, rollMapper(x));
  analogWrite(PITCH, pitchMapper(x));
  analogWrite(YAW, yawMapper(x));
}
