#include <SoftwareSerial.h>
#include "constants.h"

int distances[10] = {0};

byte **data_map = NULL;

/**
 * Sonars
 */
Ultrasonic Front(FRONT_TRIG, FRONT_ECHO);
Ultrasonic Right(RIGHT_TRIG, RIGHT_ECHO);
Ultrasonic Left(LEFT_TRIG, LEFT_ECHO);
Ultrasonic Back(BACK_TRIG, BACK_ECHO);

byte distance_front = 0;
byte distance_back = 0;
byte distance_left = 0;
byte distance_right = 0;

unsigned int current_x = BASIC_SIZE / 2;
unsigned int current_y = BASIC_SIZE / 2;

/**
 * current direction of the copter
 */
byte current_direction = FRONT;


void go_forward(int distance) {
    switch (current_direction) {
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
    current_direction += 1;
    if (current_direction > LEFT) {
        current_direction = FRONT;
    }
}

void go_turn_left() {
    current_direction -= 1;
    if (current_direction < 0) {
        current_direction = LEFT;
    }
}

byte distance_from(Ultrasonic &sonic)
{
    long microsec = sonic.timing();
    unsigned int result = Front.convert(microsec, Ultrasonic::CM);
    if (result > THRESHOLD) {
        return TOO_FAR;
    }
    return result;
}

void set_to_map(byte value, unsigned int x, unsigned int y)
{
    data_map[x][y] = value;
}

void check_and_set(byte distance, unsigned int dx, unsigned int dy)
{
    if (distance == TOO_FAR) {
        set_to_map(EMPTY, current_x + dx, current_y + dy);
    } else {
        set_to_map(OBSTACLE, current_x + dx, current_y + dy);        
    }
}

void send_data(byte front, byte left, byte right, byte back, byte dx, byte dy, byte direction) 
{
    byte package[] = {front, left, right, back, dx, dy, direction};
    Serial.write(package, PACKAGE_SIZE); //BT is connected to the Serial.
}

void setup() {
    Serial.begin(9600); 

    data_map = (byte **) calloc(BASIC_SIZE, sizeof(byte *));
    for (int i = 0; i < BASIC_SIZE; ++i) {
        data_map[i] = (byte *) calloc(BASIC_SIZE, sizeof(byte));
    }

    //TODO: copter input pins initialization
}

void loop() {
    distance_front = distance_from(Front);
    distance_back = distance_from(Back);
    distance_left = distance_from(Left);
    distance_right = distance_from(Right);

    send_data(distance_front, distance_left, distance_right, distance_back, 1, 1, current_direction);

    check_and_set(distance_front, 1, 0);
    check_and_set(distance_back, -1, 0);
    check_and_set(distance_left, 0, -1);
    check_and_set(distance_right, -1, 0);

    if (distance_front == TOO_FAR) {
        go_forward(ONE_STEP);
    } else {
        go_turn_right();
    }
}
