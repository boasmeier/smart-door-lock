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
#include "WifiConnectionHandler.hpp"
#include "MyMqttClient.hpp"
#include "MqttTopics.hpp"
#include "secrets.hpp"
#include "DoorlockConfig.h"

#define LOG_PRINTFLN(fmt, ...)  printfln_P(PSTR(fmt), ##__VA_ARGS__)
#define LOG_SIZE_MAX 128
void printfln_P(const char *fmt, ...) {
  char buf[LOG_SIZE_MAX];
  va_list ap;
  va_start(ap, fmt);
  vsnprintf_P(buf, LOG_SIZE_MAX, fmt, ap);
  va_end(ap);
  Serial.println(buf);
}

// the setup function runs once when you press reset or power the board
MyMqttClient *mqtt;
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(9600);
  while(!Serial) {
    continue;
  }

  LOG_PRINTFLN("Test logger %d", 150);

  char ssid[] = SECRET_SSID;
  char pass[] = SECRET_PASS;
  WifiConnectionHandler connHandl = WifiConnectionHandler();
  connHandl.scanNetworks();
  connHandl.connectWPA2(ssid, pass);
  
  mqtt = new MyMqttClient(MQTT_HOST, MQTT_PORT);
}

// the loop function runs over and over again forever
void loop() {
  mqtt->publish(MqttTopics::DOOR_STATE, "{ doorState: open }");
  delay(5000);
}
