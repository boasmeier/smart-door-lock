#include <SPI.h>
#include <WiFiNINA.h>
#include "WifiConnectionHandler.hpp"
#include "SerialLogger.hpp"

WifiConnectionHandler::WifiConnectionHandler() {
  if(WiFi.status() == WL_NO_MODULE) {
    SERIAL_ERROR("Communication with WiFi module failed!");
    for(;;){ }
  }

  String fv = WiFi.firmwareVersion();
  if(fv > WIFI_FIRMWARE_LATEST_VERSION) {
    SERIAL_INFO("Please upgrage the firmware");
  }

  byte mac[6];
  WiFi.macAddress(mac);
  SERIAL_INFO("MAC: %02X:%02X:%02X:%02X:%02X:%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
}

void WifiConnectionHandler::scanNetworks() {
  SERIAL_INFO("Scanning for nearby networks...");
  int numSsid = WiFi.scanNetworks();
  if (numSsid == -1) {
    SERIAL_ERROR("Couldn't get a wifi connection");
    for(;;){}
  }

  SERIAL_INFO("number of available networks: %d", numSsid);
  for (int thisNet = 0; thisNet < numSsid; thisNet++) {
    SERIAL_INFO("%d)%s %s \tSignal: %i dBm", thisNet, WiFi.SSID(thisNet), getEncryptionType(WiFi.encryptionType(thisNet)), WiFi.RSSI(thisNet));
  }
}

void WifiConnectionHandler::connectWPA2(char ssid[], char pass[]) {
  while (m_status != WL_CONNECTED) {
    SERIAL_INFO("Attempting to connect to WPA SSID: %s", ssid);
    m_status = WiFi.begin(ssid, pass);
    delay(10000);
  }
  SERIAL_INFO("You're connected to the network");
  printCurrentNet();
  printWifiData();
}

int WifiConnectionHandler::getStatus() {
  return m_status;
}

String WifiConnectionHandler::getIp() {
  IPAddress ip = WiFi.localIP();
  return ipAddress2String(ip);
}

const char* WifiConnectionHandler::getSsid() {
  return WiFi.SSID();
}

void WifiConnectionHandler::getMac(byte mac[]) {
  WiFi.macAddress(mac);
}

void WifiConnectionHandler::getBssid(byte bssid[]) {
  WiFi.BSSID(bssid);
}

const char* WifiConnectionHandler::getEncryptionType(int thisType) {
  switch(thisType) {
    case ENC_TYPE_WEP:
      return "WEP";
      break;
    case ENC_TYPE_TKIP:
      return "WPA";
      break;
    case ENC_TYPE_CCMP:
      return "WPA2";
      break;
    case ENC_TYPE_NONE:
      return "None";
      break;
    case ENC_TYPE_AUTO:
      return "Auto";
      break;
    case ENC_TYPE_UNKNOWN:
    default:
      return "Unknown";
      break;
  }
}

String WifiConnectionHandler::ipAddress2String(const IPAddress& ipAddress)
{
  return String(ipAddress[0]) + String(".") +\
  String(ipAddress[1]) + String(".") +\
  String(ipAddress[2]) + String(".") +\
  String(ipAddress[3])  ; 
}

void WifiConnectionHandler::printWifiData() {
  // print IP address of arduino
  IPAddress ip = WiFi.localIP();
  SERIAL_INFO("IP Address of arduino: %s", ipAddress2String(ip).c_str());

  // print MAC of arduino
  byte mac[6];
  WiFi.macAddress(mac);
  SERIAL_INFO("MAC address of arduino: %02X:%02X:%02X:%02X:%02X:%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
}

void WifiConnectionHandler::printCurrentNet() {
  // print the SSID of the network the arduino is connected to:
  SERIAL_INFO("SSID: %s", WiFi.SSID());
  
  // print the MAC address of the router the arduino is connected to:
  byte bssid[6];
  WiFi.BSSID(bssid);
  SERIAL_INFO("BSSID: %02X:%02X:%02X:%02X:%02X:%02X", bssid[0], bssid[1], bssid[2], bssid[3], bssid[4], bssid[5]);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  SERIAL_INFO("Signal strength (RSSI): %d", rssi);

  // print the encryption type:
  byte encryption = WiFi.encryptionType();
  SERIAL_INFO("Encryption Type: %s", getEncryptionType(encryption));
}
