/*
 * UidEepromStore.hpp
 * Created on 2021-07-12
 * 
 * Copyright(c) 2021 HSLU.
 * This software is the proprietary information of HSLU. 
 * Author: Boas Meier boas.meier@stud.hslu.ch 
*/
#ifndef UID_EEPROM_STORE_H_
#define UID_EEPROM_STORE_H_

#include "../config/DoorlockConfig.h"

class UidEepromStore {
    public:
        UidEepromStore();
        void loadFromEeprom();
        bool contains(String uid);
        int getUidCount();
        const char* m_uids[MAX_UID_COUNT];
        

    private:
        int m_uidCount;
        
};

#endif // UID_EEPROM_STORE_H_
