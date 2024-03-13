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
    FluidNCCmd fluidnccmd;
    uint16_t speed = 0;
    if(MessageQueueHolder::msgQueueFluidNC.receive(fluidnccmd,1)) {
        switch(fluidnccmd.speed) {
            case JoyStickSpeed::zeroSpeed:
                speed = 0;
            break;
            case JoyStickSpeed::slowSpeed:
                speed = 500;
            break;
            case JoyStickSpeed::middleSpeed:
                speed = 1000;
            break;
            case JoyStickSpeed::fastSpeed:
                speed = 2000;
            break;
        }
        switch(fluidnccmd.cmd) {
            case FluidNCData::poweroff:

            break;
            case FluidNCData::quit:
                Serial.println("[vTaskFluidNC::readFromMessageQueue] quit");
                fluidNC->unlock();
            break;
            case FluidNCData::jogCancel:
                Serial.println("[vTaskFluidNC::readFromMessageQueue] jogCancel");
                fluidNC->jogCanel();
            break;
            case FluidNCData::homing:
                Serial.println("[vTaskFluidNC::readFromMessageQueue] homing");
                fluidNC->homing();
            break;
            case FluidNCData::setXLeft:
                Serial.print("[vTaskFluidNC::readFromMessageQueue] setX-, ");
                Serial.println(speed);
                fluidNC->driveXaxis(speed,false);
            break;
            case FluidNCData::setXRight:
                Serial.print("[vTaskFluidNC::readFromMessageQueue] setX+, ");
                Serial.println(speed);
                fluidNC->driveXaxis(speed,true);
            break;
            case FluidNCData::setYLeft:
                Serial.print("[vTaskFluidNC::readFromMessageQueue] setY-, ");
                Serial.println(speed);
                fluidNC->driveYaxis(speed,false);
            break;
            case FluidNCData::setYRight:
                Serial.print("[vTaskFluidNC::readFromMessageQueue] setY+, ");
                Serial.println(speed);
                fluidNC->driveYaxis(speed,true);
            break;
            case FluidNCData::setZUp:
                Serial.print("[vTaskFluidNC::readFromMessageQueue] setZ+, ");
                Serial.println(speed);
                fluidNC->driveZaxis(speed,false);
            break;
            case FluidNCData::setZDown:
                Serial.print("[vTaskFluidNC::readFromMessageQueue] setZ-, ");
                Serial.println(speed);
                fluidNC->driveZaxis(speed,true);
            break;
        }
    }
}
void vTaskFluidNC::Run(void *p)
{   
    vTaskFluidNC& r_this = GetInstance();
    r_this.fluidNC->getGrblState(false);

    while (true)
    {
        if(r_this.fluidNC->isConnected()== true) {
            Serial.println("[vTaskFluidNC::Run] Fluid NC connected");
            r_this.readFromMessageQueue();
        } else {
            //Serial.println("[vTaskFluidNC::Run] Fluid NC not connected");
            //ONLY FOR TEST REASONS
            r_this.readFromMessageQueue();
        }
        vTaskDelay(100 / portTICK_PERIOD_MS);
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



