/*
 * CardReader.cpp
 * Created on 2021-10-10
 * 
 * Copyright(c) 2021 HSLU.
 * This software is the proprietary information of HSLU. 
 * Author: Boas Meier boas.meier@stud.hslu.ch 
*/
#include <Arduino.h>
#include "CardReader.hpp"
#include "../connection/PahoMqttClient.hpp"
#include "../connection/MqttTopics.hpp"
#include "../logger/SerialLogger.hpp"
#include "../logger/MqttLogger.hpp"
#include "../lib/pn532/pn532.h"
#include "../lib/pn532/pn532_uno.h"

CardReader::CardReader() {
    uint8_t buff[255];
    PN532_SPI_Init(&m_pn532);
    if(PN532_GetFirmwareVersion(&m_pn532, buff) == PN532_STATUS_OK) {
        SERIAL_INFO("Found PN532 with firmware version: %d.%d", buff[1], buff[2]);
        MQTT_INFO(mqtt, "Found PN532 with firmware version: %d.%d", buff[1], buff[2]);
    }
    PN532_SamConfiguration(&m_pn532);
}

static volatile unsigned long previousTime = 0;
static volatile unsigned long enterTime = 0;
String CardReader::read() {
    // This is needed because WiFiNINA library communicates over SPI with wifichip
    // and the pn532 library doesn't do a proper chip select. Therefore we just call 
    // the initialization again which sends chip select signal.    
    PN532_SPI_Init(&m_pn532);

    // Read target with timeout of 1000ms and check if authorized.
    uint8_t uid[MIFARE_UID_MAX_LENGTH];
    int32_t uidLen = 0;
    String uidString;
    uidLen = PN532_ReadPassiveTarget(&m_pn532, uid, PN532_MIFARE_ISO14443A, 1000);
    if(uidLen == PN532_STATUS_ERROR) {
        return String("");
    }
    else {
        enterTime = millis();
        if(enterTime-previousTime > 2000) {
            uidString = uidToString(uid, uidLen);
            SERIAL_INFO("Detected card with UID: %s", uidString.c_str());
            MQTT_INFO(mqtt, "Detected card with UID: %s", uidString.c_str());
            previousTime = enterTime;
            return uidString;
        }
        else {
            return String("");
        }
    }
}

String CardReader::uidToString(uint8_t uid[], int32_t len) {
    String stringUid;
    for (uint8_t i = 0; i < len; i++) {
        if (uid[i] <= 0xF) {
            stringUid += String("0");
        }
        stringUid += String(uid[i], HEX);
        if(i < len-1) {
            stringUid += String(" ");
        } 
    }
    return stringUid;
}