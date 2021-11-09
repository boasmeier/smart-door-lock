#pragma once

#include <WiFiNINA.h>



class WifiConnectionHandler {
  public:
    WifiConnectionHandler();
    void scanNetworks();
    void connectWPA2(char ssid[], char pass[]);
    int getStatus();
    String getIp();
    const char* getSsid();
    void getMac(byte mac[]);
    void getBssid(byte bssid[]);
    

  private:
    const char* getEncryptionType(int thisType);
    void printWifiData();
    void printCurrentNet();
    String ipAddress2String(const IPAddress& ipAddress);

    int m_status = WL_IDLE_STATUS;
    const char* ip;
    const char* ssid;
  
};

static WifiConnectionHandler *connHandl;
