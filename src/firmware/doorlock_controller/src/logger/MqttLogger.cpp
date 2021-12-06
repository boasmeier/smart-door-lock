/*
 * MqttLogger.cpp
 * Created on 2021-10-10
 * 
 * Copyright(c) 2021 HSLU.
 * This software is the proprietary information of HSLU. 
 * Author: Boas Meier boas.meier@stud.hslu.ch  
*/
#include <Arduino.h>
#include <stdarg.h>
#include "MqttLogger.hpp"
#include "../connection/PahoMqttClient.hpp"
#include "../connection/MqttTopics.hpp"

void MqttLogger::debug(PahoMqttClient *client, const char *fmt, ...) {
  char msg[LOG_SIZE_MAX];
  strcpy(msg, "DEBUG: ");
  char buf[LOG_SIZE_MAX - strlen(msg)];
  va_list ap;
  va_start(ap, fmt);
  vsnprintf_P(buf, LOG_SIZE_MAX, fmt, ap);
  va_end(ap);
  strcat(msg, buf);
  client->publish(MqttTopics::LOG_TELEMETRY, msg);
}

void MqttLogger::info(PahoMqttClient *client, const char *fmt, ...) {
  char msg[LOG_SIZE_MAX];
  strcpy(msg, "INFO: ");
  char buf[LOG_SIZE_MAX - strlen(msg)];
  va_list ap;
  va_start(ap, fmt);
  vsnprintf_P(buf, LOG_SIZE_MAX, fmt, ap);
  va_end(ap);
  strcat(msg, buf);
  client->publish(MqttTopics::LOG_TELEMETRY, msg);
}

void MqttLogger::warning(PahoMqttClient *client, const char *fmt, ...) {
  char msg[LOG_SIZE_MAX];
  strcpy(msg, "WARNING: ");
  char buf[LOG_SIZE_MAX - strlen(msg)];
  va_list ap;
  va_start(ap, fmt);
  vsnprintf_P(buf, LOG_SIZE_MAX, fmt, ap);
  va_end(ap);
  strcat(msg, buf);
  client->publish(MqttTopics::LOG_TELEMETRY, msg);
}

void MqttLogger::error(PahoMqttClient *client, const char *fmt, ...) {
  char msg[LOG_SIZE_MAX];
  strcpy(msg, "ERROR: ");
  char buf[LOG_SIZE_MAX - strlen(msg)];
  va_list ap;
  va_start(ap, fmt);
  vsnprintf_P(buf, LOG_SIZE_MAX, fmt, ap);
  va_end(ap);
  strcat(msg, buf);
  client->publish(MqttTopics::LOG_TELEMETRY, msg);
}
