/*
 * NunchukController.cpp
 *
 *  Created on: Jun 11, 2021
 *      Author: Jacob
 */

#include "nunchukController.hpp"

#include <stdio.h>

#include "driver/i2c.h"
#include "hal/i2c_types.h"
#include "esp_log.h"
#include "esp_err.h"

static const char *TAG = "NunchukController";

// for nunchuk I2C data 
static volatile uint8_t nunchukBuffer[NUNCHUK_CONTROLLER_BUFFER_SZ];


NunchukController* NunchukController::nunchuk = nullptr;


NunchukController* NunchukController::getInstance(i2c_port_t i2cPort, uint8_t i2cAddr)
{
	if (nunchuk == nullptr)
	{
		nunchuk = new NunchukController(i2cPort, i2cAddr);
	}
	return nunchuk;
}

void NunchukController::initi2c() {
    i2c_config_t i2cConfig;
	i2cConfig.mode = I2C_MODE_MASTER;
	i2cConfig.scl_io_num = I2C_SCL_PIN;
	i2cConfig.sda_io_num = I2C_SDA_PIN;
	i2cConfig.scl_pullup_en = GPIO_PULLUP_ENABLE;
	i2cConfig.sda_pullup_en = GPIO_PULLUP_ENABLE;
	i2cConfig.clk_flags = 0;
	i2cConfig.master.clk_speed = I2C_FREQ_HZ;
	ESP_ERROR_CHECK(i2c_param_config(I2C_PORT_NUM, &i2cConfig));
	ESP_ERROR_CHECK(i2c_driver_install(I2C_PORT_NUM, I2C_MODE_MASTER, 0, 0, 0));
}


NunchukController::NunchukController(i2c_port_t i2cPort, uint8_t i2cAddr
    ) : port(i2cPort), addr(i2cAddr)
{
    initi2c();
    // initialize, disable encryption
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (addr<<1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, 0xF0, true);
    i2c_master_write_byte(cmd, 0x55, true);
    i2c_master_write_byte(cmd, 0xFB, true);
    i2c_master_write_byte(cmd, 0x00, true);
    i2c_master_stop(cmd);
    i2c_master_cmd_begin(port, cmd, 10/portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);

    // fetch once
    fetchLatestReadings();

    ESP_LOGI(TAG, "initialized with port=%d, addr=0x%X", (int)port, (int)addr);
}


/*
 *  can get ~500 readings/sec if FreeRTOS tick rate is set to 1000Hz
 *  only ~100 readings/sec at 100Hz
 */ 
void NunchukController::fetchLatestReadings()
{
    // get data frame
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (addr<<1) | I2C_MASTER_READ, true);
    i2c_master_read(cmd, (uint8_t*)&nunchukBuffer[0], NUNCHUK_CONTROLLER_BUFFER_SZ-1, I2C_MASTER_ACK);
    // NACK on last byte
    i2c_master_read_byte(cmd, (uint8_t*)&nunchukBuffer[NUNCHUK_CONTROLLER_BUFFER_SZ-1], I2C_MASTER_NACK);
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(port, cmd, 1/portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);

    // extract and store
    if (ret == ESP_OK) {
        btnAccelByte = nunchukBuffer[NUNCHUK_CONTROLLER_BTN_ACCEL_IDX];
        joystickdata.JX = nunchukBuffer[NUNCHUK_CONTROLLER_JOYSTICK_X_IDX];
        joystickdata.JY = nunchukBuffer[NUNCHUK_CONTROLLER_JOYSTICK_Y_IDX];
        joystickdata.AX = (uint16_t)((nunchukBuffer[NUNCHUK_CONTROLLER_ACCEL_X_IDX] << 2) | 
                        ((btnAccelByte & 0b11000000) >> 6));
        joystickdata.AY = (uint16_t)((nunchukBuffer[NUNCHUK_CONTROLLER_ACCEL_Y_IDX] << 2) | 
                        ((btnAccelByte & 0b00110000) >> 4));
        joystickdata.AZ = (uint16_t)((nunchukBuffer[NUNCHUK_CONTROLLER_ACCEL_Z_IDX] << 2) | 
                        ((btnAccelByte & 0b00001100) >> 2));
        joystickdata.C = (uint8_t)(!((btnAccelByte & 0b10) >> 1));
        joystickdata.Z = (uint8_t)(!(btnAccelByte & 0b1));
    }
    
    // request for next time
    cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (addr<<1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, 0x00, true);
    i2c_master_stop(cmd);
    i2c_master_cmd_begin(port, cmd, 1/portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);
}


//nunchuk_data_t* NunchukController::getLatestData()  { return &latestNunchukData; }
uint8_t         NunchukController::getJoystickX()       { return joystickdata.JX;}
uint8_t         NunchukController::getJoystickY()       { return joystickdata.JY;}
uint16_t        NunchukController::getAccelX()          { return joystickdata.AX;}
uint16_t        NunchukController::getAccelY()          { return joystickdata.AY;}
uint16_t        NunchukController::getAccelZ()          { return joystickdata.AZ;}
uint8_t         NunchukController::getCButton()         { return joystickdata.C; }
uint8_t         NunchukController::getZButton()         { return joystickdata.Z; }
JoystickData    NunchukController::getMovementCommand() {return joystickdata;    }


