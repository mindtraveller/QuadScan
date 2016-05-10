#include <SoftwareSerial.h>

#include "Ultrasonic.h"

#define FrontTrigPin A5 
#define FrontEchoPin A4
#define RightTrigPin A3
#define RightEchoPin A2
#define LeftTrigPin A1
#define LeftEchoPin A0
#define BackTrigPin 13
#define BackEchoPin 12


Ultrasonic Front(FrontTrigPin, FrontEchoPin); 
Ultrasonic Right(RightTrigPin, RightEchoPin); 
Ultrasonic Left(LeftTrigPin, LeftEchoPin); 
Ultrasonic Back(BackTrigPin, BackEchoPin);

void setup() {
	Serial.begin(9600); 
}

void loop() {
	unsigned int FrontSm, LeftSm, RightSm, BackSm;
	long FrontMicrosec = Front.timing();
	long LeftMicrosec = Left.timing();
	long RightMicrosec = Right.timing();
	long BackMicrosec = Back.timing();

	FrontSm = Front.convert(FrontMicrosec, Ultrasonic::CM); 
	LeftSm = Left.convert(LeftMicrosec, Ultrasonic::CM); 
	RightSm = Right.convert(RightMicrosec, Ultrasonic::CM); 
	BackSm = Back.convert(BackMicrosec, Ultrasonic::CM);
	Serial.print("Front : "); 
	Serial.print(FrontSm); 
	Serial.print(" Left : ");
	Serial.print(LeftSm); 
	Serial.print(" Right : "); 
	Serial.print(RightSm); 
	Serial.print(" Back : "); Serial.println(BackSm);
	delay(100); 
}
