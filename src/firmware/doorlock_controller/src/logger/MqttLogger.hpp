/*
 * MqttLogger.hpp
 * Created on 2021-10-10
 * 
 * Copyright(c) 2021 HSLU.
 * This software is the proprietary information of HSLU. 
 * Author: Boas Meier boas.meier@stud.hslu.ch  
*/
#ifndef MQTT_LOGGER_H_
#define MQTT_LOGGER_H_

#include <Arduino.h>
#include <stdarg.h>
#include "../connection/PahoMqttClient.hpp"
#include "../config/DoorlockConfig.h"

#define MQTT_DEBUG(client, fmt, ...) MqttLogger::debug(client, PSTR(fmt), ##__VA_ARGS__)
#define MQTT_INFO(client, fmt, ...) MqttLogger::info(client, PSTR(fmt), ##__VA_ARGS__)
#define MQTT_WARNING(client, fmt, ...) MqttLogger::warning(client, PSTR(fmt), ##__VA_ARGS__)
#define MQTT_ERROR(client, fmt, ...) MqttLogger::error(client, PSTR(fmt), ##__VA_ARGS__)

class MqttLogger {
  public:
    MqttLogger();
    static void debug(PahoMqttClient *client, const char *fmt, ...);
    static void info(PahoMqttClient *client, const char *fmt, ...);
    static void warning(PahoMqttClient *client, const char *fmt, ...);
    static void error(PahoMqttClient *client, const char *fmt, ...);
};

#endif // MQTT_LOGGER_H_
