#include "JoystickHandling.hpp"

Joystick::Joystick() : lastState(false), startTime(0), deviCtrX(125), deviCtrY(125) {
}

void Joystick::update(uint8_t x, uint8_t y) {
/*  |              .`     Up    `.                |
    |            .`       |       `.              |
    |          .`         |         `.            |
    |        .`           |           `.          |
    |      .`             |             `.        |
    |    .`               |               `.      |
    |  .`  Left ----------0---------- Right `.    |
    |   `.                |                 .`    |
    |     `.              |               .`      |
    |       `.            |             .`        |
    |         `.          |           .`          |
    |           `.        |         .`            |
    |             `.     Down     .`              |*/
   getDirection(x,y);
}
// Function to determine the direction based on X and Y values
void Joystick::getDirection(uint8_t xVal, uint8_t yVal) {
    //Serial.print("[Joystick::getDirection]");
    //Serial.print(xVal);
    //Serial.println(yVal);
    JoyStickDirections directionCmd;
    JoyStickSpeed speedCmd;
    // Calculate the deviation from the center for X and Y axes
    int xDelta = abs(xVal - 125); // Center is assumed to be around 512
    int yDelta = abs(yVal - 125);
    const int threshold = 5;
    // Check if joystick movement exceeds the threshold
    if (xDelta > threshold || yDelta > threshold) {
        // Calculate the angle
        float angle = (atan2(yVal - deviCtrY, xVal - deviCtrX) * 180 / PI);

        // Determine the direction based on the angle
        if (angle > -22.5 && angle <= 22.5) {
            directionCmd = JoyStickDirections::right;
        } else if (angle > 22.5 && angle <= 67.5) {
            directionCmd = JoyStickDirections::upRight;
        } else if (angle > 67.5 && angle <= 112.5) {
            directionCmd = JoyStickDirections::up;
        } else if (angle > 112.5 && angle <= 157.5) {
            directionCmd = JoyStickDirections::upLeft;
        } else if (angle > 157.5 || angle <= -157.5) {
            directionCmd = JoyStickDirections::left;
        } else if (angle > -157.5 && angle <= -112.5) {
            directionCmd = JoyStickDirections::downLeft;
        } else if (angle > -112.5 && angle <= -67.5) {
            directionCmd = JoyStickDirections::down;
        } else {
            directionCmd = JoyStickDirections::downRight;
        }

        // Calculate the hypotenuse (distance from the center)
        float speed = sqrt(xDelta * xDelta + yDelta * yDelta);
        if(speed < 33) {
            speedCmd = JoyStickSpeed::slowSpeed;
        } else if(speed < 66) {
            speedCmd = JoyStickSpeed::middleSpeed;
        } else if (speed < 100) {
            speedCmd = JoyStickSpeed::fastSpeed;
        }

        directionCallback(directionCmd,speedCmd);
    } else {
        deviCtrX = xVal;     //35-224
        deviCtrY = yVal;     //25-215
        directionCmd = JoyStickDirections::joystick_idle;
    }
}

void Joystick::setCallback(void (*callback)(JoyStickDirections, JoyStickSpeed)) {
    directionCallback = callback;
}