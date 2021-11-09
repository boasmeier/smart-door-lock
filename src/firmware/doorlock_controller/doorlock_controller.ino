/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/
#include <SPI.h>
#include <WiFiNINA.h>
#include "src/connection/WifiConnectionHandler.hpp"
#include "src/connection/MyMqttClient.hpp"
#include "src/connection/MqttTopics.hpp"
#include "src/config/secrets.hpp"
#include "src/config/DoorlockConfig.h"
#include "src/logger/MqttLogger.hpp"
#include "src/logger/SerialLogger.hpp"

#include "src/door/Lock.hpp"
#include "src/door/DoorSwitch.hpp"
#include "src/door/MotionSensor.hpp"
#include "src/door/Door.hpp"


// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(9600);
  while(!Serial) {
    continue;
  }

  // set up connection to gateway
  connectToWifi();
  mqtt = new MyMqttClient(MQTT_HOST, MQTT_PORT);
  logSuccessfullConnectionToGateway();
  
  (*mqtt).m_mqttClient.onMessage(onMqttMessage);
  mqtt->subscribeTo("gateway/1/action/unlock");
  mqtt->subscribeTo("gateway/1/action/lock");
  
  // set up door
  Lock lock(LOCK_LED_PIN, LockState::LOCKED);
  DoorSwitch doorSwitch(DOOR_SWITCH_PIN);
  MotionSensor motionSensor(MOTION_SENSOR_PIN);
  door = new Door(lock, doorSwitch, motionSensor);
}

// the loop function runs over and over again forever
void loop() {

  mqtt->publish(MqttTopics::DOOR_STATE, "{ \"doorState\": \"open\" }");
  mqtt->publish(MqttTopics::LOCK_STATE, "{ \"lockState\": \"locked\" }");
  
  mqtt->publish(MqttTopics::INTRUSION_EVENT, "Intrusion event");
  mqtt->publish(MqttTopics::SUSPICIOUS_ACTIVITY_EVENT, "Suspicious Activity");
  mqtt->publish(MqttTopics::RING_EVENT, "Ring event");

  MQTT_INFO(mqtt, "Test logger %d", 42);
  
  delay(10000);
}

void connectToWifi() {
  char ssid[] = SECRET_SSID;
  char pass[] = SECRET_PASS;
  connHandl = new WifiConnectionHandler();
  connHandl->scanNetworks();
  connHandl->connectWPA2(ssid, pass);
}

void logSuccessfullConnectionToGateway() {
  MQTT_INFO(mqtt, "Arduino connected to network with ssid: %s", connHandl->getSsid());
  MQTT_INFO(mqtt, "IP Address of arduino: %s", connHandl->getIp().c_str());
  byte mac[6];
  connHandl->getMac(mac);
  MQTT_INFO(mqtt, "MAC address of arduino: %02X:%02X:%02X:%02X:%02X:%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  byte bssid[6];
  connHandl->getBssid(bssid);
  MQTT_INFO(mqtt, "BSSID: %02X:%02X:%02X:%02X:%02X:%02X", bssid[0], bssid[1], bssid[2], bssid[3], bssid[4], bssid[5]);
  MQTT_INFO(mqtt, "Arduino connected to broker %s:%d", MQTT_HOST, MQTT_PORT);
}


