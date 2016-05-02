#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "Ultrasonic.h"

#define FrontTrigPin A5 
#define FrontEchoPin A4
#define RightTrigPin A3
#define RightEchoPin A2
#define LeftTrigPin A1
#define LeftEchoPin A0
#define BackTrigPin 13
#define BackEchoPin 12


const byte THRESHOLD = 150;
const byte TOO_FAR = 255;
const byte ONE_STEP = 1;


// map cells
const byte NOT_SET = 0;
const byte EMPTY = 1;
const byte OBSTACLE = 2;


enum DIRECTION {
    FRONT, RIGHT, BACK, LEFT
};


// map size
const byte BASIC_SIZE = 30;


#endif // CONSTANTS_H
