#ifndef WIFIHOST_HPP
#define WIFIHOST_HPP
#include "Arduino.h"
#include <WifiClientSecure.h>
#include <WiFiManager.h>


class WifiHost
{
public:
    WifiHost(int configPortalTimeout, int connectTimeout);
    bool connectToWifi(const char* name);
    bool disconnectFromWifi(void);

private:
    WiFiManager manager; 
    int this_configPortalTimeout;
    int this_connectTimeout;

};
#endif