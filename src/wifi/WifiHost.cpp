#include "WifiHost.hpp"

WifiHost::WifiHost(int configPortalTimeout, int connectTimeout) 
:this_configPortalTimeout(configPortalTimeout), this_connectTimeout(connectTimeout) {

}



bool WifiHost::connectToWifi(const char* name) {
    //manager.setConfigPortalBlocking(true);
    Serial.println("[WifiHost::connectToWifi] connectToWifi");
    manager.setConfigPortalTimeout(this_configPortalTimeout);
    manager.setConnectTimeout(this_connectTimeout);
    manager.setHostname(name);
    if(manager.autoConnect(name)) {
        
        Serial.println("\n[SETUP] Local IP: "); Serial.print(WiFi.localIP());
        return false;
    }
    Serial.println("There is no Wifi Connection, not even afer 90 sec Timeout");
    return true;
}

bool WifiHost::disconnectFromWifi(void) {
    return manager.disconnect();
}
