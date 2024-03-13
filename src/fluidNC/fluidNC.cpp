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


void FluidNC::getGrblState(bool full){
    myCNC.getGrblState(full);
}

/* UNLOCK command when FluidNC is in ALARM mode */
void FluidNC::unlock() {
    switch (myCNC.mState()) {
        case Alarm:
            myCNC.Unlock();
        break;
        case Run:
            myCNC.FeedHold();
        break;
        case Hold:
            myCNC.CycleStartResume();
        break;
    }
}

void FluidNC::homing() {
    myCNC.Home();
}

void FluidNC::jogCanel() {
    myCNC.JogCancel();
}


void FluidNC::driveXaxis(uint16_t speed, bool direction) {
        /* mState: Unknwn, Alarm, Idle, Jog, Home, Check, Run, Cycle, Hold, Door, Sleep*/
    if(myCNC.mState() == Idle) {
        #define MAX_SPEED 5000
        #define MAX_JOGSTR 50
        char jogStr[MAX_JOGSTR];
        
        float distance = 0;
        if (direction == true) {
            distance = 0.001 * (speed > MAX_SPEED ? MAX_SPEED : speed);
        }
        else {
            distance = -0.001 * (speed > MAX_SPEED ? MAX_SPEED : speed);
        }
        snprintf(jogStr, MAX_JOGSTR, "$J=G21G91X%fY0Z0F%d", distance, speed);
        myCNC.fluidCMD(jogStr);
    } else {
        Serial.println("[FluidNC::driveXaxis] Machine not in IDLE State");
    }
}

void FluidNC::driveYaxis(uint16_t speed, bool direction) {
    
    /* mState: Unknwn, Alarm, Idle, Jog, Home, Check, Run, Cycle, Hold, Door, Sleep*/
    if(myCNC.mState() == Idle) {
        #define MAX_SPEED 5000
        #define MAX_JOGSTR 50
        char jogStr[MAX_JOGSTR];
        
        float distance = 0;
        if (direction == true) {
            distance = 0.001 * (speed > MAX_SPEED ? MAX_SPEED : speed);
        }
        else {
            distance = -0.001 * (speed > MAX_SPEED ? MAX_SPEED : speed);
        }
        snprintf(jogStr, MAX_JOGSTR, "$J=G21G91X0Y%fZ0F%d", distance, speed);
        myCNC.fluidCMD(jogStr);
    } else {
        Serial.println("[FluidNC::driveYaxis] Machine not in IDLE State");
    }
}

void FluidNC::driveZaxis(uint16_t speed, bool direction) {
    
    /* mState: Unknwn, Alarm, Idle, Jog, Home, Check, Run, Cycle, Hold, Door, Sleep*/
    if(myCNC.mState() == Idle) {
        #define MAX_SPEED 5000
        #define MAX_JOGSTR 50
        char jogStr[MAX_JOGSTR];
        
        float distance = 0;
        if (direction == true) {
            distance = 0.001 * (speed > MAX_SPEED ? MAX_SPEED : speed);
        }
        else {
            distance = -0.001 * (speed > MAX_SPEED ? MAX_SPEED : speed);
        }
        snprintf(jogStr, MAX_JOGSTR, "$J=G21G91X0Y0Z%fF%d", distance, speed);
        myCNC.fluidCMD(jogStr);
    } else {
        Serial.println("[FluidNC::driveZaxis] Machine not in IDLE State");
    }
}

