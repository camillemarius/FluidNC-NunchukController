#include <Arduino.h>
#include "wifi/WifiHost.hpp"
#include "fluidNC/fluidNC.hpp"
#include "nunchuck/nunchukController.hpp"

WifiHost *wifi;
FluidNC *fluidNC;


void setup() {

  Serial.begin(115200);
  wifi = new WifiHost(60,60);
  //fluidNC = new FluidNC();

  //buttonRED.init(PIN_RED);
  // ButtonConfig* buttonREDconfig = buttonRED.getButtonConfig();
  // buttonREDconfig->setFeature(ButtonConfig::kFeatureLongPress);
  // buttonREDconfig->setFeature(ButtonConfig::kFeatureSuppressAfterLongPress);

  wifi->connectToWifi("nunchuck"); 
  //fluidNC->getGrblState(false);

}

void loop() {
  Serial.println("[MAIN::loop] allive");

  NunchukController* nunchuk = NunchukController::getInstance(); 
  nunchuk->fetchLatestReadings();
  Serial.println("");
  Serial.print("AccelX:   ");   Serial.println(nunchuk->getAccelX());
  Serial.print("AccelY:   ");   Serial.println(nunchuk->getAccelY());
  Serial.print("AccelZ:   ");   Serial.println(nunchuk->getAccelZ());
  Serial.print("X:        ");   Serial.println(nunchuk->getJoystickX());
  Serial.print("Y:        ");   Serial.println(nunchuk->getJoystickY());
  Serial.print("Button C: "); Serial.println(nunchuk->getCButton());
  Serial.print("Button Z: "); Serial.println(nunchuk->getZButton());

  delay(1000);
    
  //sinceStart = millis();
  //activeTimer(false);
  
  //checkRotateA();
  //checkJoystick();

  //buttonREMS.check();
  //buttonGREEN.check();
  //buttonYELLOW.check();
  //buttonRED.check();


    /*if (myCNC.isConnected() && lastUpdate +  statusUpdateInterval<millis()){
        DEBUG_SERIAL.println("[MAIN:loop] Status update...");
        DEBUG_SERIAL.flush();
        //checkBattery();
        getGrblState(true);
        checkConnect();
        ////tftUpdate(false);
        lastUpdate = millis();
    }*/
}
