#include <Arduino.h>
#include <stdarg.h>
#include "MqttLogger.hpp"
#include "MyMqttClient.hpp"
#include "MqttTopics.hpp"

void MqttLogger::info(MyMqttClient *client, const char *fmt, ...) {
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

void MqttLogger::error(MyMqttClient *client, const char *fmt, ...) {
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
