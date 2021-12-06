#include <Arduino.h>
#include "MyMqttClient.hpp"
#include "MqttMessageHandler.hpp"
#include "../logger/SerialLogger.hpp"
#include "../config/DoorlockConfig.h"
#include <util/atomic.h>



MyMqttClient::MyMqttClient(const char *broker, int port): m_mqttClient(m_wifiClient), _broker(broker), _port(port) {
  SERIAL_INFO("Attempting to connect to the MQTT broker: %s", _broker);
  if (!m_mqttClient.connect(_broker, _port)) {
    SERIAL_ERROR("MQTT connection failed! Error code = %d", m_mqttClient.connectError());
    for(;;) { }
  }
  SERIAL_INFO("You're connected to the MQTT broker!");
}

void MyMqttClient::publish(const char *topic, const char *msg) {
  SERIAL_INFO("Sending message to topic:  %s, msg: %s", topic, msg);
  m_mqttClient.beginMessage(topic);
  m_mqttClient.print(msg);
  m_mqttClient.endMessage();
}

void MyMqttClient::subscribeTo(const char *topic) {
  SERIAL_INFO("Subscribing to topic:  %s", topic);
  m_mqttClient.subscribe(topic);
}

void MyMqttClient::poll() {
  m_mqttClient.poll();
}

void MyMqttClient::handleMqttMessage() {
    // take first message
    int n = QUEUE_SIZE;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
      /*
      for(int i=0; i<n; i++) {
          SERIAL_INFO("%d", mqttMessagePointerQueue[i]);
      }*/
      if(mqttMessagePointerQueue[0] != -1) {
          MqttMessageHandler::handleMessage(mqttMessagePointerQueue[0]->getTopic(), mqttMessagePointerQueue[0]->getMessage());
          // remove first element and move the others one space ahead
          for(int i=0; i<n-2; i++) {
              mqttMessagePointerQueue[i] = mqttMessagePointerQueue[i+1];
          }
          mqttMessagePointerQueue[n-1] = (MqttMessage*) -1;
      }
    }
}


void onMqttMessage(int messageSize) {
  String msg = "";
  String topic = (*mqtt).m_mqttClient.messageTopic();
  while((*mqtt).m_mqttClient.available()) {
    char c = (char)(*mqtt).m_mqttClient.read();
    msg.concat(c);
  }
  // append to queue
  for(int i=0; i<QUEUE_SIZE; i++) {
    if(mqttMessagePointerQueue[i] != -1) {
      continue;
    }
    else {
      mqttMessagePointerQueue[i] = new MqttMessage(topic, msg);
      break;
    }
  }
}
