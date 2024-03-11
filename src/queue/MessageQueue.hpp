#include "templates/MessageQueueTemplate.hpp"
/*-----------------------------------------------------------------------
-- MessageQueues 
-----------------------------------------------------------------------*/
template<typename T>
class MessageQueueJoystick : public MessageQueueTemplate<T> {
    public:
     MessageQueueJoystick();
};

template<typename T>
MessageQueueJoystick<T>::MessageQueueJoystick() : MessageQueueTemplate<T>(5) {}
