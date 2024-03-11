#include "fluidNC.hpp"


FluidNC::FluidNC() {
    bool conn = myCNC.connect(fluidnc_host, fluidnc_port);
    if (!conn)
    {
        Serial.println("[SETUP] Not connected, entering deep sleep mode.");
        delay(2000);
        //goto_sleep();
    }
    else 
    {
        Serial.println("[SETUP] Connected! ID: "); Serial.print(myCNC.activeID());
        // Test Command
        cSF(setup_test,1,"\n");
        cSF (myReply, 5);
        myCNC.cmd2(setup_test, myReply);
        Serial.println("[SETUP] ID: ");Serial.print(myCNC.activeID());
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

