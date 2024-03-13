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
        if(MessageQueueHolder::msgQueueJoystick.receive(r_this.nunchuckData,10)) {
            switch(r_this.nunchuckData.cButtonHandling) {
                FluidNCCmd fluidnccmd;
                case ButtonHandling::button_idle:
                break;
                case ButtonHandling::shortPressed:
                    fluidnccmd.cmd = FluidNCData::jogCancel;
                    MessageQueueHolder::msgQueueFluidNC.send(fluidnccmd,1);
                break;
                case ButtonHandling::longPressed:
                    fluidnccmd.cmd = FluidNCData::quit;
                    MessageQueueHolder::msgQueueFluidNC.send(fluidnccmd,1);
                break;
            }

            switch(r_this.nunchuckData.zButtonHandling) {
                FluidNCCmd fluidnccmd;
                case ButtonHandling::button_idle:
                break;
                case ButtonHandling::shortPressed:
                    fluidnccmd.cmd = FluidNCData::homing;
                    MessageQueueHolder::msgQueueFluidNC.send(fluidnccmd,1);
                break;
                case ButtonHandling::longPressed:
                    Serial.print("[vTaskFluidNCNunchukController::zButtonCallback::longPressed]:");
                    Serial.println("Z");
                break;
            }

            FluidNCCmd fluidnccmd;
            fluidnccmd.speed = r_this.nunchuckData.joystickspeed;
            switch(r_this.nunchuckData.joystickdirection) {
                case JoyStickDirections::joystick_idle:
                break;
                case JoyStickDirections::up:
                    if(r_this.nunchuckData.zButtonHandling == ButtonHandling::pressing) {

                    } else {
                        fluidnccmd.cmd = FluidNCData::setYRight;
                        MessageQueueHolder::msgQueueFluidNC.send(fluidnccmd,1);
                    }
                break;
                case JoyStickDirections::upRight:
                    //Serial.print("[vTaskFluidNCNunchukController::vTaskNunchuk::joystickCallback]: ");
                    //Serial.println("upRight");
                break;
                case JoyStickDirections::right:
                    fluidnccmd.cmd = FluidNCData::setXRight;
                    MessageQueueHolder::msgQueueFluidNC.send(fluidnccmd,1);
                break;
                case JoyStickDirections::downRight:
                    //Serial.print("[vTaskFluidNCNunchukController::vTaskNunchuk::joystickCallback]: ");
                    //Serial.println("downRight");
                break;
                case JoyStickDirections::down:
                    fluidnccmd.cmd = FluidNCData::setYLeft;
                    MessageQueueHolder::msgQueueFluidNC.send(fluidnccmd,1);
                break;
                case JoyStickDirections::downLeft:
                    //Serial.print("[vTaskFluidNCNunchukController::vTaskNunchuk::joystickCallback]: ");
                    //Serial.println("downLeft");
                break;
                case JoyStickDirections::left:
                    fluidnccmd.cmd = FluidNCData::setXLeft;
                    MessageQueueHolder::msgQueueFluidNC.send(fluidnccmd,1);
                break;
                case JoyStickDirections::upLeft:
                    //Serial.print("[vTaskFluidNCNunchukController::vTaskNunchuk::joystickCallback]: ");
                    //Serial.println("upLeft");
                break;
            }
        }
        
        

        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void vTaskFluidNCNunchukController::interpretInput(void) {

}

bool vTaskFluidNCNunchukController::takeNunchukSemaphore()
{
    return xSemaphoreTake(nunchukSemaphore, 0);
}

bool vTaskFluidNCNunchukController::giveNunchukSemaphore()
{
    return xSemaphoreGive(nunchukSemaphore);
}



