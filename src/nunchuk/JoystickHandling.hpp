#ifndef JOYSTICK_HANDLING_HPP
#define JOYSTICK_HANDLING_HPP

#include <Arduino.h>
enum class JoyStickDirections {
    joystick_idle,
    up,
    upRight,
    right,
    downRight,
    down,
    downLeft,
    left,
    upLeft,
};
enum class JoyStickSpeed {
    zeroSpeed,
    slowSpeed,
    middleSpeed,
    fastSpeed,
};


class Joystick {
    public:
        Joystick();
        void update(uint8_t x, uint8_t y);
        void getDirection(uint8_t xVal, uint8_t yVal);

        
        void setCallback(void (*callback)(JoyStickDirections,JoyStickSpeed));

    private:
        uint8_t lastState;
        unsigned long startTime;
        uint8_t deviCtrX;     //35-224
        uint8_t deviCtrY;     //25-215
        //JoyStickDirections directionCmd;

        void (*directionCallback)(JoyStickDirections,JoyStickSpeed);

};
#endif