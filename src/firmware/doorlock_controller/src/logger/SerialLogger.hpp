#pragma once
#include <Arduino.h>
#include <stdarg.h>

#define SERIAL_INFO(fmt, ...) SerialLogger::info(PSTR(fmt), ##__VA_ARGS__)
#define SERIAL_ERROR(fmt, ...) SerialLogger::error(PSTR(fmt), ##__VA_ARGS__)

class SerialLogger {
  public:
    SerialLogger();
    static void info(const char *fmt, ...);
    static void error(const char *fmt, ...); 
};


   
