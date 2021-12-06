#pragma once

#include <ArduinoMqttClient.h>
#include <WiFiNINA.h>
#include "MqttMessage.hpp"

class MyMqttClient {
  public:
    WiFiClient m_wifiClient;
    MqttClient m_mqttClient;

    MyMqttClient(const char *broker, int port);
    void publish(const char *topic, const char *msg);
    void subscribeTo(const char *topic);
    void poll();
    void handleMqttMessage();

    
  private:
    const char *_broker;
    int        _port     = 1883;
    //set interval for sending messages (milliseconds)
    const long _interval = 8000;
    unsigned long _previousMillis = 0;
    int _count = 0;
  
};

extern MyMqttClient *mqtt;

void onMqttMessage(int messageSize);


static MqttMessage *msg = new MqttMessage("Test", "Msg");

#define QUEUE_SIZE (10)
// use volatile and use ATOMIC_BLOCk macro to access m_eventCount because Arduino is a 8-bit mcu 
// and we access mqttMessagePointerQueue from inside an ISR
static volatile MqttMessage* mqttMessagePointerQueue[] = {(MqttMessage*)-1, (MqttMessage*)-1, (MqttMessage*)-1, (MqttMessage*)-1, (MqttMessage*)-1, (MqttMessage*)-1, (MqttMessage*)-1, (MqttMessage*)-1, (MqttMessage*)-1, (MqttMessage*)-1};
