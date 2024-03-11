#pragma once

#include <Arduino.h>
#include "queue/MessageQueueHolder.hpp"
#include "queue/templates/message.h"

class vTaskFluidNCNunchukController {
    public:
        vTaskFluidNCNunchukController();
        static void CreateResources(int priority);
        
    private:
        static void Run(void *p);
        static vTaskFluidNCNunchukController& GetInstance(void);
        void createTask(const int priority);
        void readFromMessageQueue(); 
        bool takeNunchukSemaphore();
        bool giveNunchukSemaphore();
        void interpretInput();

    private:
        TaskHandle_t nunchukTask;
        SemaphoreHandle_t nunchukSemaphore;

        JoystickData joyStickData;
};
