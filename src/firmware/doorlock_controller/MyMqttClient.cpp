#include "MyMqttClient.hpp"
#include "SerialLogger.hpp"

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
