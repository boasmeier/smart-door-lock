#include "MyMqttClient.hpp"
#include "MqttMessageHandler.hpp"
#include "../logger/SerialLogger.hpp"
#include "../config/DoorlockConfig.h"

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
  m_mqttClient.poll();
  m_mqttClient.beginMessage(topic);
  m_mqttClient.print(msg);
  m_mqttClient.endMessage();
}

void MyMqttClient::subscribeTo(const char *topic) {
  SERIAL_INFO("Subscribing to topic:  %s", topic);
  m_mqttClient.subscribe(topic);
}

void onMqttMessage(int messageSize) {
  String msg = "";
  String topic = (*mqtt).m_mqttClient.messageTopic();
  while((*mqtt).m_mqttClient.available()) {
    char c = (char)(*mqtt).m_mqttClient.read();
    msg.concat(c);
  }
  SERIAL_INFO("onMqttMessage - topic: %s - message: %s", topic.c_str(), msg.c_str());
  MqttMessageHandler::handleMessage(topic, msg);
}
