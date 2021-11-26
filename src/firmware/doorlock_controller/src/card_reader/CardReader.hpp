#pragma once
#include "Arduino.h"
#include "../lib/pn532/pn532.h"
#include "../lib/pn532/pn532_uno.h"

class CardReader {
    public:
        CardReader();
        void read();

    private:
        PN532 m_pn532;

        void checkCardPermission(String uid);
        String uidToString(uint8_t uid[], int32_t len);
        
};

extern CardReader *cardReader;