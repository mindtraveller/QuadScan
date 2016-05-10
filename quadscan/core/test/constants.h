#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "Ultrasonic.h"

/**
 * Sonars pins
 */
#define FRONT_TRIG A5 
#define FRONT_ECHO A4
#define RIGHT_TRIG A3
#define RIGHT_ECHO A2
#define LEFT_TRIG A1
#define LEFT_ECHO A0
#define BACK_TRIG 13
#define BACK_ECHO 12

/**
 * Size of package of data
 */
#define PACKAGE_SIZE 7


const byte THRESHOLD = 50;
const byte TOO_FAR = 255;
const byte ONE_STEP = 1;


/**
 * Map cells
 */
const byte NOT_SET = 0;
const byte EMPTY = 1;
const byte OBSTACLE = 2;


enum DIRECTION {
    FRONT, RIGHT, BACK, LEFT
};


/**
 * map size
 */
const byte BASIC_SIZE = 30;


//[100; 250]
#define THROTTLE 3
//[190; 250]
#define ROLL 5
//[190; 250]
#define PITCH 6
//[110; 250]
#define COLLECTIVE 9
#define FLIGHT_MODE 10
//[110; 250]
#define YAW 11

#define ROLL_MIN 190;
#define PITCH_MIN 190;
#define YAW_MIN 110;
#define COLLECTIVE_MIN 100;
#define THROTTLE_MIN 100;

#define ROLL_NEUTRAL 220;
#define PITCH_NEUTRAL 220;
#define COLLECTIVE_NEUTRAL 180;
#define YAW_NEUTRAL 180;

#define ROLL_GREATER 225;
#define ROLL_LESS 215;
#define PITCH_GREATER 225;
#define PITCH_LESS 215;

#define THROTTLE_INITIAL 105;

#define STEP 1

#endif // CONSTANTS_H
