// #ifndef NUNCHUK_CONTROLLER_ESP8266_H_
// #define NUNCHUK_CONTROLLER_ESP8266_H_

// #include <Arduino.h>
// #include <Wire.h>

// // I2C
// #define I2C_SDA_PIN                 D2
// #define I2C_SCL_PIN                 D1
// #define I2C_FREQ_HZ                 100000
// #define I2C_PORT_NUM                0

// // nunchuk
// #define NUNCHUK_CONTROLLER_I2C_PORT_NUM     0
// #define NUNCHUK_CONTROLLER_I2C_ADDR         0x52
// #define NUNCHUK_CONTROLLER_BUFFER_SZ        6
// #define NUNCHUK_CONTROLLER_JOYSTICK_X_IDX   0
// #define NUNCHUK_CONTROLLER_JOYSTICK_Y_IDX   1
// #define NUNCHUK_CONTROLLER_ACCEL_X_IDX      2
// #define NUNCHUK_CONTROLLER_ACCEL_Y_IDX      3
// #define NUNCHUK_CONTROLLER_ACCEL_Z_IDX      4
// #define NUNCHUK_CONTROLLER_BTN_ACCEL_IDX    5

// class NunchukController {
// public:
//     static NunchukController* getInstance();
//     void fetchLatestReadings();
//     uint8_t getJoystickX();
//     uint8_t getJoystickY();
//     uint16_t getAccelX();
//     uint16_t getAccelY();
//     uint16_t getAccelZ();
//     uint8_t getCButton();
//     uint8_t getZButton();
// protected:
//     NunchukController();
//     void initI2C();
// private:
//     static NunchukController* nunchuk;
//     const uint8_t addr = NUNCHUK_CONTROLLER_I2C_ADDR;
//     uint8_t joystickX, joystickY;
//     uint16_t accelX, accelY, accelZ;
//     uint8_t cButton, zButton;
//     uint8_t btnAccelByte;
// };

// #endif /* NUNCHUK_CONTROLLER_H_ */