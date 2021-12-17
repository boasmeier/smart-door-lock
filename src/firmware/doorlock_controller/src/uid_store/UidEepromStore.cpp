/*
 * UidEepromStore.cpp
 * Created on 2021-07-12
 * 
 * Copyright(c) 2021 HSLU.
 * This software is the proprietary information of HSLU. 
 * Author: Boas Meier boas.meier@stud.hslu.ch 
*/
#include <Arduino.h>
#include <EEPROM.h>
#include "UidEepromStore.hpp"
#include "../logger/SerialLogger.hpp"
#include "../logger/MqttLogger.hpp"

UidEepromStore::UidEepromStore() {
    loadFromEeprom();
    SERIAL_INFO("Successfully loaded %d uids from EEPROM into RAM.", m_uidCount);
    MQTT_INFO(mqtt, "Successfully loaded %d uids from EEPROM into RAM.", m_uidCount);
    for (int i = 0; i<m_uidCount; i++) {
        SERIAL_DEBUG("%s", m_uids[i]);
    }
}

void UidEepromStore::loadFromEeprom() {
    int a = 0;
    int value;
    int uidLenCounter = 0;
    int uidIndex = 0;
    char buf[UID_LEN];
    memset(buf, 0, UID_LEN);

    value = EEPROM.read(a);
    while(value != 255) {
        char c = (char) value;
        strncat(buf, &c, 1);

        if(uidLenCounter >= UID_LEN-1) {
            const char *p = malloc(UID_LEN*sizeof(char)+1);
            strcpy(p, buf);
            m_uids[uidIndex] = p;
            memset(buf, 0, UID_LEN);
            uidLenCounter = 0;
            uidIndex++;
        } 
        else {
            uidLenCounter++;
        }

        a++;
        value = EEPROM.read(a);
    }
    m_uidCount = uidIndex;
}

bool UidEepromStore::contains(String uid) {
    bool found = false;
    for (int i = 0; i<m_uidCount; i++) {
        String authorizedUid = String(m_uids[i]);
        if(uid.equals(m_uids[i])) {
            found = true;
            break;
        }
    }
    return found;
}

int UidEepromStore::getUidCount() {
    return m_uidCount;
}