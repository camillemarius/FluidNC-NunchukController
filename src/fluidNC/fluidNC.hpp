#ifndef FLUIDNC_HPP
#define FLUIDNC_HPP
#include <WiFiManager.h>
#include <FluidNC_WebSocket.h>

class FluidNC
{
public:
    FluidNC();
    bool isConnected();
    void getGrblState(bool full);

private:
FluidNC_WS myCNC = FluidNC_WS();

    const char *fluidnc_host = "fluidnc.local"; // this is default MDNS name, feel free to change to match your setup
    const uint16_t fluidnc_port = 81; // chnage only if FLuidNC websocket port id chnaged (rare cases)
    

};
#endif