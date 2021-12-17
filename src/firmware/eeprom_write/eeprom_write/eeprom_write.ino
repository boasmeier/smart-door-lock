/*
 * EEPROM Write
 *
 * Stores uids from uids.h into the EEPROM.
 * These values will stay in the EEPROM when the board is
 * turned off and may be retrieved later by another sketch.
 */

#include <EEPROM.h>
#include "uids.h"

void setup() {
  /** Empty setup. **/
  Serial.begin(9600);
  Serial.println("Write UIDs into EEPROM...");
  int eepromAddr = 0;
  for(int i = 0; i<UID_COUNT; i++) {
    const char* extracted = uids[i];
    Serial.println(extracted);
    Serial.print("strlen: ");
    int len = strlen(extracted);
    Serial.println(len);
    for(int j = 0; j < len; j++) {
      char val = *(extracted+j);
      //EEPROM.write(eepromAddr, val);
      Serial.print("Write: ");
      Serial.print(val);
      Serial.print(" to eeprom addr: ");
      Serial.println(eepromAddr);
      eepromAddr++;
    }
  }
  Serial.println("Done!");
  
}

int a = 0;
char value;
void loop() {
  
  value = EEPROM.read(a);

  Serial.print(a);
  Serial.print("\t");
  Serial.print(value);
  Serial.println();

  a = a + 1;

  if (a == 255)
    a = 0;

  delay(500);
  
}
