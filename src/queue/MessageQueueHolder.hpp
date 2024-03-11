#pragma once
#include "MessageQueue.hpp"
#include "templates/Message.h"



class MessageQueueHolder {
    public:
        static MessageQueueHolder& getInstance();
        static MessageQueueJoystick<JoystickData> msgQueueJoystick;

    private:
        MessageQueueHolder();
};
