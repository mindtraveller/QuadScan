#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "Ultrasonic.h"

#define FrontTrigPin A1 
#define FrontEchoPin 8
#define RightTrigPin 3 
#define RightEchoPin 2
#define LeftTrigPin 4 
#define LeftEchoPin 5
#define BackTrigPin 7 
#define BackEchoPin 6


const int TOO_FAR = 10000;
const int ONE_STEP = 1;


// map cells
const char NOT_SET = 0;
const char EMPTY = 1;
const char OBSTACLE = 2;


enum ROTATION {
    FRONT, RIGHT, BACK, LEFT
};


// map size
const int BASIC_SIZE = 30;


#endif // CONSTANTS_H
