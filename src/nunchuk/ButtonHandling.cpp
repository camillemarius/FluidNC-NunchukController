#include "ButtonHandling.hpp"

Button::Button() : lastState(false), startTime(0) {
}

void Button::update(uint8_t currentState) {
    static bool longPressTriggered = false;
    ButtonHandling buttonHandling;
    buttonHandling = ButtonHandling::button_idle;
    if (currentState != lastState) {
        if (currentState >= 1) {
            // Button pressed, record start time
            startTime = millis();
            longPressTriggered = false; // Reset long press trigger flag
        } else {
            // Button released
            if (!longPressTriggered) {
                // Calculate press duration
                unsigned long pressDuration = millis() - startTime;

                // Determine if it's a short or long press
                if (pressDuration < longPressThreshold) {
                    // Short press
                    buttonHandling = ButtonHandling::shortPressed;
                    pressCallback(buttonHandling);
                } else {
                    // Long press threshold reached, but button not released yet
                    longPressTriggered = true; // Set long press trigger flag
                    startTime = millis(); // Restart the timer for next long press detection
                }
            } else {
                // Long press already triggered, do nothing
            }
        }
        // Update button state
        lastState = currentState;
    } else if (currentState >= 1 && !longPressTriggered) {
        // Button is still pressed, check for long press trigger
        unsigned long pressDuration = millis() - startTime;
        if (pressDuration >= longPressThreshold) {
            longPressTriggered = true;
            buttonHandling = ButtonHandling::longPressed;
            pressCallback(buttonHandling);
        }
    }
}

void Button::setCallback(void (*callback)(ButtonHandling)) {
    pressCallback = callback;
}