#pragma once
#include "MessageQueue.hpp"
#include "templates/Message.h"



class MessageQueueHolder {
    public:
        static MessageQueueHolder& getInstance();
        static MessageQueueJoystick<NunchuckData> msgQueueJoystick;
        static MessageQueueJoystick<FluidNCCmd> msgQueueFluidNC;

    private:
        MessageQueueHolder();
};
