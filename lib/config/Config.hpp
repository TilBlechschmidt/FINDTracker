#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <EEPROM.h>

#include "defaults.hpp"

struct ConfigData {
    ConfigData() {
        this->data = &dataBuffer.createObject();
    }
    DynamicJsonBuffer dataBuffer;
    JsonObject* data;
};

class Config {
public:
    ConfigData data;

    Config();

    Config(int EEPROMAdress);

    void read(int address);
    void write(int EEPROMAdress);

    template<typename T>
    T get(String key) {
        return (*(this->data.data))[key];
    }
};

#endif // CONFIG_H
