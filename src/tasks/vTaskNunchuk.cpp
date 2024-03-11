#include "tasks/vTaskNunchuk.hpp"

/*--------------------------------------------------------------------------------------
-- Public Static Methods
--------------------------------------------------------------------------------------*/
void vTaskNunchuk::CreateResources(int priority) {
    vTaskNunchuk& r_this = vTaskNunchuk::GetInstance();

    r_this.nunchukSemaphore = xSemaphoreCreateBinary();
    (void) r_this.giveNunchukSemaphore();
    r_this.createTask(priority);
}

void vTaskNunchuk::createTask(const int priority) {
    xTaskCreate(this->Run, "vTaskNunchuk", 1000, NULL, priority, &nunchukTask);
}

vTaskNunchuk& vTaskNunchuk::GetInstance(void) {
    static vTaskNunchuk instance;
    return instance;
}
/*--------------------------------------------------------------------------------------
-- Public Methods
--------------------------------------------------------------------------------------*/
vTaskNunchuk::vTaskNunchuk() {

}

/*--------------------------------------------------------------------------------------
-- Private Methods
--------------------------------------------------------------------------------------*/
void vTaskNunchuk::Run(void *p)
{   
    vTaskNunchuk& r_this = GetInstance();
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    NunchukController* nunchuk = NunchukController::getInstance(); 
    while (true)
    {
        nunchuk->fetchLatestReadings();
        r_this.interpretInput(nunchuk->getMovementCommand());
        MessageQueueHolder::msgQueueJoystick.send(nunchuk->getMovementCommand(),100);

        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

void vTaskNunchuk::interpretInput(JoystickData joystickdata) {
    // Joystick X-Axis
    uint8_t thrd_X_left = 255;
    uint8_t thrd_X_right = 20;
    // if(joyStickData.JX>=thrd_X_left) {
        
    // } else if(joyStickData.JX<=thrd_X_right) {

    // }
    // Joystick Y-Axis
    uint8_t thrd_Y_left = 255;
    uint8_t thrd_Y_right = 20;
    // if(joyStickData.JY>=thrd_Y_left) {

    // } else if(joyStickData.JY<=thrd_Y_right) {

    // }
    // Joystick C-Button
    uint8_t thrd_C_released = 20;
    uint8_t thrd_C_pressed = 255;
    // if(joyStickData.C>=thrd_C_pressed) {

    // } else if(joyStickData.C<=thrd_C_released) {

    // }
    // Joystick Z-Button
    uint8_t thrd_Z_released = 20;
    uint8_t thrd_Z_pressed = 255;
    // if(joyStickData.Z>=thrd_Z_pressed) {

    // } else if(joyStickData.Z<=thrd_Z_released) {

    // }
}

bool vTaskNunchuk::takeNunchukSemaphore()
{
    return xSemaphoreTake(nunchukSemaphore, 0);
}

bool vTaskNunchuk::giveNunchukSemaphore()
{
    return xSemaphoreGive(nunchukSemaphore);
}



