#ifndef MESSAGE_H
#define MESSAGE_H

#include <Arduino.h>
#include "nunchuk/ButtonHandling.hpp"
#include "nunchuk/JoystickHandling.hpp"


struct NunchuckData {
        JoyStickDirections joystickdirection;
        JoyStickSpeed joystickspeed;
        ButtonHandling cButtonHandling;
        ButtonHandling zButtonHandling;
};

enum class FluidNCData {
        poweroff,
        jogCancel,
        pause,
        quit,
        homing,
        setXLeft,
        setXRight,
        setYLeft,
        setYRight,
        setZUp,
        setZDown,
};

struct FluidNCCmd {
        FluidNCData cmd;
        JoyStickSpeed speed;

};


#endif // MESSAGE_H















