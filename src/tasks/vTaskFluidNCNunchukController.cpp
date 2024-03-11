#include "tasks/vTaskFluidNCNunchukController.hpp"

/*--------------------------------------------------------------------------------------
-- Public Static Methods
--------------------------------------------------------------------------------------*/
void vTaskFluidNCNunchukController::CreateResources(int priority) {
    vTaskFluidNCNunchukController& r_this = vTaskFluidNCNunchukController::GetInstance();

    r_this.nunchukSemaphore = xSemaphoreCreateBinary();
    (void) r_this.giveNunchukSemaphore();
    r_this.createTask(priority);
}

void vTaskFluidNCNunchukController::createTask(const int priority) {
    xTaskCreate(this->Run, "vTaskFluidNCNunchukController", 1000, NULL, priority, &nunchukTask);
}

vTaskFluidNCNunchukController& vTaskFluidNCNunchukController::GetInstance(void) {
    static vTaskFluidNCNunchukController instance;
    return instance;
}
/*--------------------------------------------------------------------------------------
-- Public Methods
--------------------------------------------------------------------------------------*/
vTaskFluidNCNunchukController::vTaskFluidNCNunchukController() {

}

/*--------------------------------------------------------------------------------------
-- Private Methods
--------------------------------------------------------------------------------------*/
void vTaskFluidNCNunchukController::Run(void *p)
{   
    vTaskFluidNCNunchukController& r_this = GetInstance();
    vTaskDelay(1000 / portTICK_PERIOD_MS);

    while (true)
    {
        MessageQueueHolder::msgQueueJoystick.receive(r_this.joyStickData,100);

        Serial.print("[vTaskFluidNCNunchukController::Run]"); 
        Serial.print(r_this.joyStickData.JX);
        Serial.print(":"); 
        Serial.print(r_this.joyStickData.JY);
        Serial.print(" / "); 
        Serial.print(r_this.joyStickData.C);
        Serial.print(":"); 
        Serial.println(r_this.joyStickData.Z);


        vTaskDelay(400 / portTICK_PERIOD_MS);
    }
}

void vTaskFluidNCNunchukController::interpretInput(void) {
    // Joystick X-Axis
    uint8_t thrd_X_left = 255;
    uint8_t thrd_X_right = 20;
    if(joyStickData.JX>=thrd_X_left) {
        
    } else if(joyStickData.JX<=thrd_X_right) {

    }
    // Joystick Y-Axis
    uint8_t thrd_Y_left = 255;
    uint8_t thrd_Y_right = 20;
    if(joyStickData.JY>=thrd_Y_left) {

    } else if(joyStickData.JY<=thrd_Y_right) {

    }
    // Joystick C-Button
    uint8_t thrd_C_released = 20;
    uint8_t thrd_C_pressed = 255;
    if(joyStickData.C>=thrd_C_pressed) {

    } else if(joyStickData.C<=thrd_C_released) {

    }
    // Joystick Z-Button
    uint8_t thrd_Z_released = 20;
    uint8_t thrd_Z_pressed = 255;
    if(joyStickData.Z>=thrd_Z_pressed) {

    } else if(joyStickData.Z<=thrd_Z_released) {

    }
}

bool vTaskFluidNCNunchukController::takeNunchukSemaphore()
{
    return xSemaphoreTake(nunchukSemaphore, 0);
}

bool vTaskFluidNCNunchukController::giveNunchukSemaphore()
{
    return xSemaphoreGive(nunchukSemaphore);
}



