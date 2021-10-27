#include "MyMqttClient.hpp"

MyMqttClient::MyMqttClient(const char *broker, int port): m_mqttClient(m_wifiClient), _broker(broker), _port(port) {
  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(_broker);
  if (!m_mqttClient.connect(_broker, _port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(m_mqttClient.connectError());
    for(;;) { }
  }
  Serial.println("You're connected to the MQTT broker!");
  Serial.println();
}

void MyMqttClient::publish(const char *topic, const char *msg) {
  m_mqttClient.poll();

  Serial.print("Sending message to topic: ");
  Serial.println(topic);
  Serial.println(msg);
  
  m_mqttClient.beginMessage(topic);
  m_mqttClient.print(msg);
  m_mqttClient.endMessage();
  Serial.println();
}
