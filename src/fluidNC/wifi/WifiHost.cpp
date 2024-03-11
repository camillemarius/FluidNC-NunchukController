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
        Serial.print("[WifiHost::connectToWifi] Local IP: "); Serial.println(WiFi.localIP());
        return false;
    }
    Serial.println("[WifiHost::connectToWifi] No Wifi after 90 sec Timeout");
    return true;
}

bool WifiHost::disconnectFromWifi(void) {
    Serial.println("[WifiHost::connectToWifi] Wifi disconnected");
    return manager.disconnect();
}
