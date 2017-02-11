#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <EEPROM.h>

#include "defaults.hpp"

class Config {
public:
    DynamicJsonBuffer dataBuffer;
    JsonObject& data;

    Config();

    Config(int EEPROMAdress);

    void read(int address);
    void write(int EEPROMAdress);

    template<typename T>
    T get(String key) {
        return this->data[key];
    }
};

#endif // CONFIG_H
