/*
 * SerialLogger.hpp
 * Created on 2021-10-10
 * 
 * Copyright(c) 2021 HSLU.
 * This software is the proprietary information of HSLU. 
 * Author: Boas Meier boas.meier@stud.hslu.ch  
*/
#ifndef SERIAL_LOGGER_H_
#define SERIAL_LOGGER_H_

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

#endif // SERIAL_LOGGER_H_


   
