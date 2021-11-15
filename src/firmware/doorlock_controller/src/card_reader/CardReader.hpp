#pragma once
#include "Arduino.h"
#include <pn532.h>
#include <pn532_uno.h>

class CardReader {
    public:
        CardReader();
        void read();

    private:
        PN532 pn532;

        void checkCardPermission(String uid);
        String uidToString(uint8_t uid[], int32_t len);
        
};

static CardReader *cardReader;