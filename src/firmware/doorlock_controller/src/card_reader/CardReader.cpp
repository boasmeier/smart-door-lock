#include "Arduino.h"
#include "CardReader.hpp"
#include "HumanMachineInterface.hpp"
#include "../logger/SerialLogger.hpp"
#include "../door/Door.hpp"
#include <pn532.h>
#include <pn532_uno.h>

CardReader::CardReader() {
    uint8_t buff[255];
    PN532_SPI_Init(&pn532);
    if(PN532_GetFirmwareVersion(&pn532, buff) == PN532_STATUS_OK) {
        SERIAL_INFO("Found PN532 with firmware version: %d.%d", buff[1], buff[2]);
    }
    PN532_SamConfiguration(&pn532);
}

void CardReader::read() {
    uint8_t uid[MIFARE_UID_MAX_LENGTH];
    int32_t uidLen = 0;
    String uidString;
    uidLen = PN532_ReadPassiveTarget(&pn532, uid, PN532_MIFARE_ISO14443A, 1000);
    if(uidLen == PN532_STATUS_ERROR) {
        return;
    }
    else {
        uidString = uidToString(uid, uidLen);
        SERIAL_INFO("Detected card with UID: %s", uidString.c_str());
        checkCardPermission(uidString);
    }
}

void CardReader::checkCardPermission(String uid) {
    String authorizedUid = String("01 23 45 67");
    if(uid.equals(authorizedUid)) {
        SERIAL_INFO("Card with UID %s authorized and entry is granted", uid.c_str());
        cardReaderHmi->success();
        door->unlock();
    }
    else {
        SERIAL_INFO("Card with UID %s not authorized", uid.c_str());
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