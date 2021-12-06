/*
 * CardReader.hpp
 * Created on 2021-10-10
 * 
 * Copyright(c) 2021 HSLU.
 * This software is the proprietary information of HSLU. 
 * Author: Boas Meier boas.meier@stud.hslu.ch 
*/
#ifndef CARD_READER_H_
#define CARD_READER_H_

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

#endif // CARD_READER_H_