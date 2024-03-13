#pragma once

#include <Arduino.h>
#include "fluidNC/fluidNC.hpp"
#include "queue/MessageQueueHolder.hpp"
#include "queue/templates/message.h"

class vTaskFluidNC {
    public:
        vTaskFluidNC();
        static void CreateResources(int priority);
        
    private:
        static void Run(void *p);
        static vTaskFluidNC& GetInstance(void);
        void createTask(const int priority);
        void readFromMessageQueue(); 
        bool takeFluidNCSemaphore();
        bool giveFluidNCSemaphore();

    private:
        TaskHandle_t fluidNCTask;
        SemaphoreHandle_t fluidNCSemaphore;
        
        FluidNC *fluidNC;
};
