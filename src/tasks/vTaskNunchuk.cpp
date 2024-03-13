#include "tasks/vTaskNunchuk.hpp"
/*--------------------------------------------------------------------------------------
-- Public Static Methods
--------------------------------------------------------------------------------------*/
void vTaskNunchuk::CreateResources(int priority) {
    vTaskNunchuk& r_this = vTaskNunchuk::GetInstance();
    r_this.nunchukSemaphore = xSemaphoreCreateBinary();
    r_this.createTask(priority);
}

void vTaskNunchuk::createTask(const int priority) {
    xTaskCreate(this->Run, "vTaskNunchuk", 2000, NULL, priority, &nunchukTask);
}

vTaskNunchuk& vTaskNunchuk::GetInstance(void) {
    static vTaskNunchuk instance;
    return instance;
}

/*--------------------------------------------------------------------------------------
-- Public Methods
--------------------------------------------------------------------------------------*/
vTaskNunchuk::vTaskNunchuk() {
    btnC.setCallback(cButtonCallback);
    btnZ.setCallback(zButtonCallback);
    joystick.setCallback(joystickCallback);
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
        
        r_this.btnC.update(nunchuk->getCButton());
        r_this.btnZ.update(nunchuk->getZButton());
        r_this.joystick.update(nunchuk->getJoystickX(),nunchuk->getJoystickY());
        
        vTaskDelay(50 / portTICK_PERIOD_MS);
        if((r_this.nunchukdata.cButtonHandling !=ButtonHandling::button_idle) ||
           (r_this.nunchukdata.zButtonHandling !=ButtonHandling::button_idle) ||
           (r_this.nunchukdata.joystickdirection!=JoyStickDirections::joystick_idle)) {
            MessageQueueHolder::msgQueueJoystick.send(r_this.nunchukdata,1);
        }
        r_this.nunchukdata.cButtonHandling = ButtonHandling::button_idle;
        r_this.nunchukdata.zButtonHandling = ButtonHandling::button_idle;
        r_this.nunchukdata.joystickdirection = JoyStickDirections::joystick_idle;
        vTaskDelay(50 / portTICK_PERIOD_MS);
    }
}

void vTaskNunchuk::cButtonCallback(ButtonHandling btnHandling) {
    vTaskNunchuk& r_this = GetInstance();
    if(btnHandling!=ButtonHandling::button_idle) {
        r_this.nunchukdata.cButtonHandling = btnHandling;
    }
}
void vTaskNunchuk::zButtonCallback(ButtonHandling btnHandling){
    vTaskNunchuk& r_this = GetInstance();
    if(btnHandling!=ButtonHandling::button_idle) {
        r_this.nunchukdata.zButtonHandling = btnHandling;
    }
}
void vTaskNunchuk::joystickCallback(JoyStickDirections joystickDirections, JoyStickSpeed joystickspeed) {
    vTaskNunchuk& r_this = GetInstance();
    static uint16_t cnt = 0;
    if(joystickDirections!=JoyStickDirections::joystick_idle) {
        cnt++;
        if(cnt>=5) { // prevent unintentionally movements
            r_this.nunchukdata.joystickdirection = joystickDirections;
            r_this.nunchukdata.joystickspeed = joystickspeed;
        }
    } else {
        cnt = 0;
    }
}