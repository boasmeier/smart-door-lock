/*
 * WifiConnectionHandler.hpp
 * Created on 2021-10-10
 * 
 * Copyright(c) 2021 HSLU.
 * This software is the proprietary information of HSLU. 
 * Author: Boas Meier boas.meier@stud.hslu.ch 
*/
#ifndef WIFI_CONNECTION_HANDLER_H_
#define WIFI_CONNECTION_HANDLER_H_

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

extern WifiConnectionHandler *connHandl;

#endif // WIFI_CONNECTION_HANDLER_H_
