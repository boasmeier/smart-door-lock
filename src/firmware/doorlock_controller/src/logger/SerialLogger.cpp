/*
 * SerialLogger.cpp
 * Created on 2021-10-10
 * 
 * Copyright(c) 2021 HSLU.
 * This software is the proprietary information of HSLU. 
 * Author: Boas Meier boas.meier@stud.hslu.ch  
*/
#include <Arduino.h>
#include <stdarg.h>
#include "SerialLogger.hpp"
#include "../config/DoorlockConfig.h"

static void SerialLogger::info(const char *fmt, ...) {
  char msg[LOG_SIZE_MAX];
  strcpy(msg, "INFO: ");
  char buf[LOG_SIZE_MAX - strlen(msg)];
  va_list ap;
  va_start(ap, fmt);
  vsnprintf_P(buf, LOG_SIZE_MAX, fmt, ap);
  va_end(ap);
  strcat(msg, buf);
  Serial.println(msg);
}

static void SerialLogger::error(const char *fmt, ...) {
  char msg[LOG_SIZE_MAX];
  strcpy(msg, "ERROR: ");
  char buf[LOG_SIZE_MAX - strlen(msg)];
  va_list ap;
  va_start(ap, fmt);
  vsnprintf_P(buf, LOG_SIZE_MAX, fmt, ap);
  va_end(ap);
  strcat(msg, buf);
  Serial.println(msg);
}
