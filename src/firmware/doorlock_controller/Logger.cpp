#include "Logger.hpp"

Logger::Logger(MyMqttClient mqtt) : m_mqtt(mqtt) {
  
}

void Logger::info(char msg[]) {
  Serial.print("INFO: ");
  Serial.println(msg);
}

void Logger::error(char msg[]) {
  
}
