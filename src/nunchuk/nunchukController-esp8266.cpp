/*
 * NunchukController.cpp
 *
 *  Created on: Jun 11, 2021
 *      Author: Jacob
 */

/* #include "nunchukController-esp8266.hpp"


static const char *TAG = "NunchukController";

// for nunchuk I2C data 
static volatile uint8_t nunchukBuffer[NUNCHUK_CONTROLLER_BUFFER_SZ];


NunchukController* NunchukController::nunchuk = nullptr;


NunchukController* NunchukController::getInstance()
{
	if (nunchuk == nullptr)
	{
		nunchuk = new NunchukController();
	}
	return nunchuk;
}

void NunchukController::initI2C() {
  Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);
  Wire.setClock(I2C_FREQ_HZ);
}

NunchukController::NunchukController() {
  initI2C();
  // initialize, disable encryption
  Wire.beginTransmission(addr);
  Wire.write(0xF0);
  Wire.write(0x55);
  Wire.write(0xFB);
  Wire.write(0x00);
  Wire.endTransmission();

  // fetch once
  fetchLatestReadings();

  //ESP_LOGI(TAG, "initialized with address 0x%X", addr);
}

void NunchukController::fetchLatestReadings() {
  Wire.requestFrom(addr, NUNCHUK_CONTROLLER_BUFFER_SZ);
  if (Wire.available() >= NUNCHUK_CONTROLLER_BUFFER_SZ) {
    for (int i = 0; i < NUNCHUK_CONTROLLER_BUFFER_SZ; i++) {
      nunchukBuffer[i] = Wire.read();
    }

    btnAccelByte = nunchukBuffer[NUNCHUK_CONTROLLER_BTN_ACCEL_IDX];
    joystickX = nunchukBuffer[NUNCHUK_CONTROLLER_JOYSTICK_X_IDX];
    joystickY = nunchukBuffer[NUNCHUK_CONTROLLER_JOYSTICK_Y_IDX];
    accelX = (uint16_t)((nunchukBuffer[NUNCHUK_CONTROLLER_ACCEL_X_IDX] << 2) |
                        ((btnAccelByte & 0b11000000) >> 6));
    accelY = (uint16_t)((nunchukBuffer[NUNCHUK_CONTROLLER_ACCEL_Y_IDX] << 2) |
                        ((btnAccelByte & 0b00110000) >> 4));
    accelZ = (uint16_t)((nunchukBuffer[NUNCHUK_CONTROLLER_ACCEL_Z_IDX] << 2) |
                        ((btnAccelByte & 0b00001100) >> 2));
    cButton = (uint8_t)(!((btnAccelByte & 0b10) >> 1));
    zButton = (uint8_t)(!(btnAccelByte & 0b1));
  }

  // request for next time
  Wire.beginTransmission(addr);
  Wire.write(0x00);
  Wire.endTransmission();
}

uint8_t NunchukController::getJoystickX() { return joystickX; }
uint8_t NunchukController::getJoystickY() { return joystickY; }
uint16_t NunchukController::getAccelX() { return accelX; }
uint16_t NunchukController::getAccelY() { return accelY; }
uint16_t NunchukController::getAccelZ() { return accelZ; }
uint8_t NunchukController::getCButton() { return cButton; }
uint8_t NunchukController::getZButton() { return zButton; } */