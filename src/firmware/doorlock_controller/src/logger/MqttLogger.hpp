/*
 * MqttLogger.hpp
 * Created on 2021-10-10
 * 
 * Copyright(c) 2021 HSLU.
 * This software is the proprietary information of HSLU. 
 * Author: Boas Meier boas.meier@stud.hslu.ch  
*/
#ifndef MQTTLOGGER_H_
#define MQTTLOGGER_H_

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

#endif // MQTTLOGGER_H_
