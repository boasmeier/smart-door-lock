#include <Arduino.h>
#include "CardReader.hpp"
#include "HumanMachineInterface.hpp"
#include "../logger/SerialLogger.hpp"
#include "../logger/MqttLogger.hpp"
#include "../door/Door.hpp"
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

void CardReader::read() {
    // This is needed because WiFiNINA library communicates over SPI with wifichip
    // and the pn532 library doesn't do a proper chip select. Therefore we just call 
    // the initialization again which sends chip select signal.    
    PN532_SPI_Init(&m_pn532);

    // Read target with timeout of 1000ms and check if authorized.
    uint8_t uid[MIFARE_UID_MAX_LENGTH];
    int32_t uidLen = 0;
    String uidString;
    uidLen = PN532_ReadPassiveTarget(&m_pn532, uid, PN532_MIFARE_ISO14443A, 1000);
    //SERIAL_INFO("uidLen: %d", uidLen);
    //SERIAL_INFO("uid: %d", uid);
    if(uidLen == PN532_STATUS_ERROR) {
        return;
    }
    else {
        uidString = uidToString(uid, uidLen);
        SERIAL_INFO("Detected card with UID: %s", uidString.c_str());
        MQTT_INFO(mqtt, "Detected card with UID: %s", uidString.c_str());
        checkCardPermission(uidString);
    }
}

void CardReader::checkCardPermission(String uid) {
    String authorizedUid = String("01 23 45 67");
    if(uid.equals(authorizedUid)) {
        SERIAL_INFO("Card with UID %s authorized and entry is granted", uid.c_str());
        MQTT_INFO(mqtt, "Card with UID %s authorized and entry is granted", uid.c_str());
        mqtt->publish(MqttTopics::CARD_EVENT, "{ \"uid\": \"%d\", \"authorized\": \"true\"}", uid);
        cardReaderHmi->success();
        door->unlock();
    }
    else {
        SERIAL_INFO("Card with UID %s not authorized", uid.c_str());
        MQTT_INFO(mqtt, "Card with UID %s not authorized", uid.c_str());
        mqtt->publish(MqttTopics::CARD_EVENT, "{ \"uid\": \"%d\", \"authorized\": \"false\"}", uid);
        cardReaderHmi->failure();
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