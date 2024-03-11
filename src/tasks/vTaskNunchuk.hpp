#pragma once

#include <Arduino.h>
#include "nunchuk/nunchukController.hpp"
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
        bool takeNunchukSemaphore();
        bool giveNunchukSemaphore();
        void interpretInput(JoystickData nunchuk);

    private:
        TaskHandle_t nunchukTask;
        SemaphoreHandle_t nunchukSemaphore;
};
