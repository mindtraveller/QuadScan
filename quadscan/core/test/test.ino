#include <SoftwareSerial.h>
#include "constants.h"

int throttle_value = THROTTLE_INITIAL;
int roll_value = ROLL_NEUTRAL;
int pitch_value = PITCH_NEUTRAL;
int collective_value = COLLECTIVE_NEUTRAL;
int yaw_value = YAW_NEUTRAL;

byte front_distance = 0;
byte back_distance = 0;
byte left_distance = 0;
byte right_distance = 0;

bool isInitialized = false;

/**
 * Sonars
 */
Ultrasonic Front(FRONT_TRIG, FRONT_ECHO);
Ultrasonic Right(RIGHT_TRIG, RIGHT_ECHO);
Ultrasonic Left(LEFT_TRIG, LEFT_ECHO);
Ultrasonic Back(BACK_TRIG, BACK_ECHO);

byte distance_from(Ultrasonic &sonic)
{
    long microsec = sonic.timing();
    unsigned int result = sonic.convert(microsec, Ultrasonic::CM);
    if (result > THRESHOLD) {
        return TOO_FAR;
    }
    return result;
}

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

  if (isInitialized) {
    front_distance = distance_from(Front);
    back_distance = distance_from(Back);
    left_distance = distance_from(Left);
    right_distance = distance_from(Right);

    if (front_distance < THRESHOLD) {
      pitch_value = PITCH_GREATER;
    } else if (back_distance < THRESHOLD) {
      pitch_value = PITCH_LESS;
    } else {
      pitch_value = PITCH_NEUTRAL;
    }
    
    if (left_distance < THRESHOLD) {
      roll_value = ROLL_LESS;
    } else if (right_distance < THRESHOLD) {
      roll_value = ROLL_GREATER;
    } else {
      roll_value = ROLL_NEUTRAL;
    }

    analogWrite(PITCH, pitch_value);
    analogWrite(ROLL, roll_value);
  }

  if (Serial.available()) {
    char value = Serial.read();
    switch(value) {
      case 't':
        throttle_value -= STEP;
        analogWrite(THROTTLE, throttle_value);
        break;
      case 'T':
        throttle_value += STEP;
        analogWrite(THROTTLE, throttle_value);
        break;
      case 'r':
        roll_value -= STEP;
        analogWrite(ROLL, roll_value);
        break;
      case 'R':
        roll_value += STEP;
        analogWrite(ROLL, roll_value);
        break;
      case 'p':
        pitch_value -= STEP;
        analogWrite(PITCH, pitch_value);
        break;
      case 'P':
        pitch_value += STEP;
        analogWrite(PITCH, pitch_value);
        break;
      case 'y':
        yaw_value -= STEP;  
        analogWrite(YAW, yaw_value);
        break;
      case 'Y':
        yaw_value += STEP;  
        analogWrite(YAW, yaw_value);
        break;
      case 'c':
        collective_value -= STEP;  
        analogWrite(COLLECTIVE, collective_value);
        break;
      case 'C':
        collective_value += STEP;  
        analogWrite(COLLECTIVE, collective_value);
        break;
      case 's':
        isInitialized = true;
        
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
  
        delay(100);
        
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
    Serial.print("trottle: ");
    Serial.println(throttle_value);
    Serial.print("roll: ");
    Serial.println(roll_value);
    Serial.print("pitch: ");
    Serial.println(pitch_value);
    Serial.println("\n");
  }

//  Serial.print("trottle: ");
//  Serial.println(throttle_value);
//  Serial.print("roll: ");
//  Serial.println(roll_value);
//  Serial.print("pitch: ");
//  Serial.println(pitch_value);
//  Serial.println("\n");
//  Serial.println(yaw_value);
//  Serial.println(collective_value);
}
