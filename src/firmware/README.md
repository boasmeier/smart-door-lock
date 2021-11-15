# Smart Door Lock Firmware
This folder contains all the code running on the Arduino Uno. It communicates with sensors and the gateway.

[[_TOC_]]

## Dependencies
The door lock firmware depends on following arduino libraries. These libraries are available over the arduino library manager.
* [WiFiNINA](https://github.com/arduino-libraries/WiFiNINA)
* [ArduinoMqttClient](https://github.com/arduino-libraries/ArduinoMqttClient)

On windows the source code of those libraries is usually available under the following path: <br>
`C:\Users\\[username]\Documents\Arduino\libraries\`

The door lock firmware depends on following libraries. Which aren't available over the arduino library manager.
* [pn532](https://www.waveshare.com/wiki/PN532_NFC_HAT)

## Configure Wifi
Create a file `secrets.hpp` with SSID and Pass of desired WiFi:
```
#pragma once

#define SECRET_SSID "<YourSSID>"
#define SECRET_PASS "<Password>"
```

## Configure MQTT
Add `MQTT_HOST` and `MQTT_PORT` to `DoorlockConfig.h`. e.g.:
```
#define MQTT_HOST "<Host>"
#define MQTT_PORT <Port>
```

## Arduino with VS Code
The official Arduino IDE does not support intellisense. The vs code extension [Arduino](https://marketplace.visualstudio.com/items?itemName=vsciot-vscode.vscode-arduino) offers a solution. 

To enjoy full intellisense experience the following steps are needed:
1. Install [Arduino](https://marketplace.visualstudio.com/items?itemName=vsciot-vscode.vscode-arduino) extension
2. Set Arduino Path e.g. on windows `C:\Program Files (x86)\Arduino`
3. Set Arduino Command Path to `arduino_debug.exe`
4. Set C/C++ Intellisense Engine to `Tag Parser`
5. Add path to the source code of the arduino libraries to the `IncludePath` of `c_cpp_properties.json`