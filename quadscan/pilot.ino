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

const char NOT_SET = 0;
const char EMPTY = 1;
const char OBSTACLE = 2;

enum ROTATION {
    FRONT, RIGHT, BACK, LEFT
};

const int BASIC_SIZE = 30;

int distances[10] = {0};

char **data_map = NULL;

Ultrasonic Front(FrontTrigPin, FrontEchoPin);
Ultrasonic Right(RightTrigPin, RightEchoPin);
Ultrasonic Left(LeftTrigPin, LeftEchoPin);
Ultrasonic Back(BackTrigPin, BackEchoPin);

void go_forward(int distance) {
    switch (current_rotation) {
    case FRONT:
        current_x += distance;
        if (current_x > BASIC_SIZE) { current_x -= distance; }
        break;
    case BACK:
        current_x -= distance;
        if (current_x < 0) { current_x += distance; }
        break;
    case LEFT:
        current_y -= distance;
        if (current_y < 0) { current_y += distance; }
        break;
    case RIGHT:
        current_y += distance;
        if (current_y > BASIC_SIZE) { current_y -= distance; }
        break;
    }
}

void go_turn_right() {
    current_rotation += 1;
    if (current_rotation > LEFT) {
        current_rotation = FRONT;
    }
}

void go_turn_left() {
    current_rotation -= 1;
    if (current_rotation < 0) {
        current_rotation = LEFT;
    }
}

unsigned int distance_from(Ultrasonic &sonic)
{
    long microsec = sonic.timing();
    unsigned int result = Front.convert(microsec, Ultrasonic::CM);
    if (result > 150) {
        return TOO_FAR;
    }
    return result;
}

void set_to_map(char value, unsigned int x, unsigned int y)
{
    data_map[x][y] = value;
}

void check_and_set(unsigned int distance, unsigned int dx, unsigned int dy)
{
    if (distance == TOO_FAR) {
        set_to_map(EMPTY, current_x + dx, current_y + dy);
    } else {
        set_to_map(OBSTACLE, current_x + dx, current_y + dy);        
    }
}

void setup() {
    Serial.begin(9600);

    data_map = (char **) calloc(BASIC_SIZE, sizeof(char *));
    for (int i = 0; i < BASIC_SIZE; ++i) {
        data_map[i] = (char *) calloc(BASIC_SIZE, sizeof(char));
    }
}

unsigned int distance_front = 0;
unsigned int distance_back = 0;
unsigned int distance_left = 0;
unsigned int distance_right = 0;

unsigned int current_x = BASIC_SIZE / 2;
unsigned int current_y = BASIC_SIZE / 2;
char current_rotation = FRONT;

void loop() {
    distance_front = distance_from(Front);
    distance_back = distance_from(Back);
    distance_left = distance_from(Left);
    distance_right = distance_from(Right);

    check_and_set(distance_front, 1, 0);
    check_and_set(distance_back, -1, 0);
    check_and_set(distance_left, 0, -1);
    check_and_set(distance_right, -1, 0);

    if (distance == TOO_FAR) {
        go_forward(ONE_STEP);
    } else {
        go_turn_right();
    }
}
