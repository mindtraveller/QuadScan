#include "constants.h"

Ultrasonic Front(FrontTrigPin, FrontEchoPin); 

void go_forward(int distance) {
    // implementation
}

void go_turn_right() {
    // implementation
}

unsigned int distance_from(Ultrasonic &sonic)
{
    long microsec = sonic.timing();
    unsigned int result = Front.convert(microsec, Ultrasonic::CM);
    if (result > 300) {
        return TOO_FAR;
    }
    return result;
}

void setup() {
    Serial.begin(9600); 
}

unsigned int distance = 0;

void loop() {
    distance = distance_from(Front);

    if (distance == TOO_FAR) {
        go_forward(ONE_STEP);
    } else {
        go_turn_right();
    }
}
