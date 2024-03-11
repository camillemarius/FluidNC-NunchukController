
#include "MessageQueueHolder.hpp"

MessageQueueJoystick<JoystickData> MessageQueueHolder::msgQueueJoystick;

MessageQueueHolder::MessageQueueHolder() {
    
}

MessageQueueHolder& MessageQueueHolder::getInstance() {
    static MessageQueueHolder holder;
    return holder;
}