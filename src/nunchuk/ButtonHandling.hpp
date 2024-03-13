#ifndef BUTTONHANDLING_HPP
#define BUTTONHANDLING_HPP

#include <Arduino.h>
enum class ButtonHandling{
    button_idle,
    pressing,
    shortPressed,
    longPressed
};

class Button {
    public:
        Button();
        void update(uint8_t currentState);
        void setCallback(void (*callback)(ButtonHandling));
    private:
        uint8_t lastState;
        unsigned long startTime;

        static const unsigned long longPressThreshold = 1000; // milliseconds

        void (*pressCallback)(ButtonHandling);


};

#endif
