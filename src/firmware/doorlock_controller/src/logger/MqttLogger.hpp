#pragma once
#include <Arduino.h>
#include <stdarg.h>
#include "../connection/MyMqttClient.hpp"
#include "../config/DoorlockConfig.h"


#define MQTT_INFO(client, fmt, ...) MqttLogger::info(client, PSTR(fmt), ##__VA_ARGS__)
#define MQTT_ERROR(client, fmt, ...) MqttLogger::error(client, PSTR(fmt), ##__VA_ARGS__)

class MqttLogger {
  public:
    MqttLogger();
    static void info(MyMqttClient *client, const char *fmt, ...);
    static void error(MyMqttClient *client, const char *fmt, ...);
};
