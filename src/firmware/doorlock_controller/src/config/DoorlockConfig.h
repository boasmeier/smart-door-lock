/*
 * DoorlockConfig.h
 * Created on 2021-10-10
 * 
 * Copyright(c) 2021 HSLU.
 * This software is the proprietary information of HSLU. 
 * Author: Boas Meier boas.meier@stud.hslu.ch 
*/
#ifndef DOORLOCK_CONFIG_H_
#define DOORLOCK_CONFIG_H_

#include "../connection/PahoMqttClient.hpp"

#define DEVICE_ID "1"

//#define MQTT_HOST "192.168.21.112"   // ip/hostname of gateway here
//#define MQTT_HOST "192.168.0.222"      // notebook @home boas 
//#define MQTT_HOST "raspberry31"
#define MQTT_HOST "192.168.31.97"       // raspberry31
#define MQTT_PORT 1884

//#define MQTT_HOST "broker.emqx.io" 
//#define MQTT_PORT 1883



#define MAX_UID_COUNT 10
#define UID_LEN 11

#define LOG_SIZE_MAX 128
#define HMI_BLINK_FREQUENCY 2

// definition of used gpio pins
#define LOCK_LED_PIN 7
#define DOOR_LED_PIN_RED 8
#define DOOR_LED_PIN_GREEN 9
#define DOORBELL_PIN 12
#define DOOR_SWITCH_PIN_CLOSE 10
#define DOOR_SWITCH_PIN_OPEN 13
#define MOTION_SENSOR_PIN 5

#endif // DOORLOCK_CONFIG_H_

