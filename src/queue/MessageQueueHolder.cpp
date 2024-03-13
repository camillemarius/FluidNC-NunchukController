
#include "MessageQueueHolder.hpp"

MessageQueueJoystick<NunchuckData> MessageQueueHolder::msgQueueJoystick;
MessageQueueJoystick<FluidNCCmd> MessageQueueHolder::msgQueueFluidNC;

MessageQueueHolder::MessageQueueHolder() {
    
}

MessageQueueHolder& MessageQueueHolder::getInstance() {
    static MessageQueueHolder holder;
    return holder;
}