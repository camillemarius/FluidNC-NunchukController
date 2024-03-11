#include "fluidNC.hpp"


FluidNC::FluidNC() {
    // Connect to local Wifi
    wifi = new WifiHost(60,60);
    wifi->connectToWifi("nunchuck"); 

    // Connect with Fluid NC
    bool conn = myCNC.connect(fluidnc_host, fluidnc_port);
    if (!conn)
    {
        Serial.println("[FluidNC::FluidNC] Not connected, entering deep sleep mode.");
        delay(2000);
        //goto_sleep();
    }
    else 
    {
        Serial.println("[FluidNC::FluidNC] Connected! ID: "); Serial.print(myCNC.activeID());
        // Test Command
        cSF(setup_test,1,"\n");
        cSF (myReply, 5);
        myCNC.cmd2(setup_test, myReply);
        Serial.println("[FluidNC::FluidNC] ID: ");Serial.print(myCNC.activeID());
        Serial.println(myReply);
    }
}

bool FluidNC::isConnected() {
    return myCNC.isConnected();
}


void FluidNC::getGrblState(bool full)
{
    myCNC.getGrblState(full);
}

