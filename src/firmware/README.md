# Smart Door Lock Firmware
This folder contains all the code running on the Arduino Uno. It communicates with sensors and the gateway.

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