#pragma once
#include "MyMqttClient.hpp"

class Logger {
  public:
    Logger(MyMqttClient mqtt);
    void info(char msg[]);
    void error(char msg[]);

  private:
    MyMqttClient m_mqtt;
};


   
