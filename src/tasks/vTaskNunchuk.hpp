#pragma once

#include <Arduino.h>
#include "nunchuk/nunchukController.hpp"
#include "nunchuk/ButtonHandling.hpp"
#include "nunchuk/JoyStickHandling.hpp"
#include "queue/MessageQueueHolder.hpp"
#include "queue/templates/message.h"
class vTaskNunchuk {
    public:
        vTaskNunchuk();
        static void CreateResources(int priority);
        
    private:
        static void Run(void *p);
        static vTaskNunchuk& GetInstance(void);
        void createTask(const int priority);
        void interpretInput(JoystickData nunchuk);

        static void cButtonCallback(ButtonHandling);
        static void zButtonCallback(ButtonHandling);
        
        static void joystickCallback(JoyStickDirections,JoyStickSpeed);

    private:
        TaskHandle_t nunchukTask;
        SemaphoreHandle_t nunchukSemaphore;

        Button btnC, btnZ;
        Joystick joystick;
        NunchuckData nunchukdata;
};
