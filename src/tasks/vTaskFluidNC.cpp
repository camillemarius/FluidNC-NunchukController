#include "tasks/vTaskFluidNC.hpp"

/*--------------------------------------------------------------------------------------
-- Public Static Methods
--------------------------------------------------------------------------------------*/
void vTaskFluidNC::CreateResources(int priority) {
    vTaskFluidNC& r_this = vTaskFluidNC::GetInstance();

    r_this.fluidNCSemaphore = xSemaphoreCreateBinary();
    (void) r_this.giveFluidNCSemaphore();
    r_this.createTask(priority);
}

void vTaskFluidNC::createTask(const int priority) {
    xTaskCreate(this->Run, "vTaskFluidNC", 5000, NULL, priority, &fluidNCTask);
}

vTaskFluidNC& vTaskFluidNC::GetInstance(void) {
    static vTaskFluidNC instance;
    return instance;
}
/*--------------------------------------------------------------------------------------
-- Public Methods
--------------------------------------------------------------------------------------*/
vTaskFluidNC::vTaskFluidNC() {
    fluidNC = new FluidNC();
}

/*--------------------------------------------------------------------------------------
-- Private Methods
--------------------------------------------------------------------------------------*/
void vTaskFluidNC::readFromMessageQueue() {
    // Message msg;
    // if(MessageQueueHolder::receive_cmd(msg, 10)) {
    //     vTaskFluidNC& r_this = GetInstance();
    // }
}
void vTaskFluidNC::Run(void *p)
{   
    vTaskFluidNC& r_this = GetInstance();
    r_this.fluidNC->getGrblState(false);

    while (true)
    {
        if(r_this.fluidNC->isConnected()== true) {
            Serial.println("[vTaskFluidNC::Run] Fluid NC connected");
        } else {
            Serial.println("[vTaskFluidNC::Run] Fluid NC not connected");
        }
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}

bool vTaskFluidNC::takeFluidNCSemaphore()
{
    return xSemaphoreTake(fluidNCSemaphore, 0);
}

bool vTaskFluidNC::giveFluidNCSemaphore()
{
    return xSemaphoreGive(fluidNCSemaphore);
}



