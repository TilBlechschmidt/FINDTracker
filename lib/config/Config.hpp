#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <EEPROM.h>

#include "defaults.hpp"

struct ConfigData {
    ConfigData() : data(dataBuffer.createObject()) {}
    ConfigData(JsonObject d) : data(d) {}
    DynamicJsonBuffer dataBuffer;
    JsonObject& data;
    // // Wireless related settings
    // uint16_t wifiReconnectionInterval;
    // String SSID;
    // String passphrase;
    //
    // // Tracking related settings
    // bool active;
    // uint16_t bufferSize;
    //
    // // Tracking server related settings
    // String trackingURL;
    // String trackingGroup;
    // String trackingUser;
};

class Config {
public:
    ConfigData data;

    Config();

    Config(int EEPROMAdress);

    void read(int address);
    void write(int EEPROMAdress);
};

#endif // CONFIG_H
