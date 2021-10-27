#include <SPI.h>
#include <WiFiNINA.h>
#include "WifiConnectionHandler.hpp"

WifiConnectionHandler::WifiConnectionHandler() {
  if(WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    for(;;){ }
  }

  String fv = WiFi.firmwareVersion();
  if(fv > WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrage the firmware");
  }

  byte mac[6];
  WiFi.macAddress(mac);
  Serial.print("MAC: ");
  printMacAddress(mac);
}

void WifiConnectionHandler::scanNetworks() {
  Serial.println("Scanning for nearby networks...");
  int numSsid = WiFi.scanNetworks();
  if (numSsid == -1) {
    Serial.println("Couldn't get a wifi connection");
    for(;;){}
  }

  Serial.print("number of available networks: ");
  Serial.println(numSsid);
  for (int thisNet = 0; thisNet < numSsid; thisNet++) {
    Serial.print(thisNet);
    Serial.print(")");
    Serial.print(WiFi.SSID(thisNet));
    Serial.print("\tSignal:");
    Serial.print(WiFi.RSSI(thisNet));
    Serial.print(" dBm ");
    printEncryptionType(WiFi.encryptionType(thisNet));
  }
  Serial.println();
}

void WifiConnectionHandler::connectWPA2(char ssid[], char pass[]) {
  while (m_status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    m_status = WiFi.begin(ssid, pass);
    delay(10000);
  }
  Serial.print("You're connected to the network");
  printCurrentNet();
  printWifiData();
}

int WifiConnectionHandler::getStatus() {
  return m_status;
}

void WifiConnectionHandler::printMacAddress(byte mac[]) {
  for (int i = 5; i >= 0; i--) {
    if (mac[i] < 16) {
      Serial.print("0");
    }
    Serial.print(mac[i], HEX);
    if (i > 0) {
      Serial.print(":");
    }
  }
  Serial.println();
}

void WifiConnectionHandler::printEncryptionType(int thisType) {
  switch(thisType) {
    case ENC_TYPE_WEP:
      Serial.println("WEP");
      break;
    case ENC_TYPE_TKIP:
      Serial.println("WPA");
      break;
    case ENC_TYPE_CCMP:
      Serial.println("WPA2");
      break;
    case ENC_TYPE_NONE:
      Serial.println("None");
      break;
    case ENC_TYPE_AUTO:
      Serial.println("Auto");
      break;
    case ENC_TYPE_UNKNOWN:
    default:
      Serial.println("Unknown");
      break;
  }
}

void WifiConnectionHandler::printWifiData() {
  // print IP address of arduino
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address of arduino: ");
  Serial.println(ip);

  // print MAC of arduino
  byte mac[6];
  WiFi.macAddress(mac);
  Serial.print("MAC address of arduino: ");
  printMacAddress(mac);
}

void WifiConnectionHandler::printCurrentNet() {
  // print the SSID of the network the arduino is connected to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  
  // print the MAC address of the router the arduino is connected to:
  byte bssid[6];
  WiFi.BSSID(bssid);
  Serial.print("BSSID: ");
  printMacAddress(bssid);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("Signal strength (RSSI): ");
  Serial.println(rssi);

  // print the encryption type:
  byte encryption = WiFi.encryptionType();
  Serial.print("Encryption Type: ");
  Serial.println(encryption, HEX);
  Serial.println();
}
