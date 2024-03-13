#ifndef FLUIDNC_HPP
#define FLUIDNC_HPP
#include <WiFiManager.h>
#include <FluidNC_WebSocket.h>
#include "fluidNC/wifi/WifiHost.hpp"

class FluidNC
{
public:
    FluidNC();
    bool isConnected();
    void getGrblState(bool full);
    void unlock();
    void homing();
    void jogCanel();
    void driveXaxis(uint16_t speed, bool direction);
    void driveYaxis(uint16_t speed, bool direction);
    void driveZaxis(uint16_t speed, bool direction);

private:
    FluidNC_WS myCNC = FluidNC_WS();
    WifiHost *wifi;

    const char *fluidnc_host = "fluidnc.local"; // this is default MDNS name, feel free to change to match your setup
    const uint16_t fluidnc_port = 81; // chnage only if FLuidNC websocket port id chnaged (rare cases)
    

};
#endif