#include <Arduino.h>
#include "tasks/vTaskNunchuk.hpp"
#include "tasks/vTaskFluidNC.hpp"
#include "tasks/vTaskFluidNCNunchukController.hpp"


#define DEBUG


void setup() {

  Serial.begin(115200);
  #ifdef DEBUG
      Serial.setDebugOutput(true);
  #else
      Serial.setDebugOutput(false);
  #endif

  vTaskFluidNC::CreateResources(1);
  vTaskNunchuk::CreateResources(1);
  vTaskFluidNCNunchukController::CreateResources(1);
}

void loop() {
  delay(1000);
    
  //sinceStart = millis();
  //activeTimer(false);

    /*if (myCNC.isConnected() && lastUpdate +  statusUpdateInterval<millis()){
        DEBUG_SERIAL.println("[MAIN:loop] Status update...");
        DEBUG_SERIAL.flush();
        //checkBattery();
        getGrblState(true);
        checkConnect();
        lastUpdate = millis();
    }*/
}
