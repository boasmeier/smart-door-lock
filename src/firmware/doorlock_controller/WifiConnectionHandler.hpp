#pragma once

#include <WiFiNINA.h>

class WifiConnectionHandler {
  public:
    WifiConnectionHandler();
    void scanNetworks();
    void connectWPA2(char ssid[], char pass[]);
    int getStatus();

  private:
    void printMacAddress(byte mac[]);
    void printEncryptionType(int thisType);
    void printWifiData();
    void printCurrentNet();

    int m_status = WL_IDLE_STATUS;
  
};
