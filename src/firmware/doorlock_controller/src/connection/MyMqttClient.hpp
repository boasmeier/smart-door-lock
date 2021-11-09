#pragma once

#include <ArduinoMqttClient.h>
#include <WiFiNINA.h>

class MyMqttClient {
  public:
    WiFiClient m_wifiClient;
    MqttClient m_mqttClient;

    MyMqttClient(const char *broker, int port);
    void publish(const char *topic, const char *msg);
    void subscribeTo(const char *topic);
    
  private:
    const char *_broker;
    int        _port     = 1883;
    //set interval for sending messages (milliseconds)
    const long _interval = 8000;
    unsigned long _previousMillis = 0;
    int _count = 0;
  
};

static MyMqttClient *mqtt;

void onMqttMessage(int messageSize);