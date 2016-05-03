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


const byte THRESHOLD = 150;
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


#endif // CONSTANTS_H
