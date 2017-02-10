#ifndef NETWORKING_H
#define NETWORKING_H

#include <ESP8266WiFi.h>

#include "Config.hpp"

class Radio {
    Config* config;

public:
    Radio(Config* conf) : config(conf) {}

    void setup();
    bool connect();
    bool connected();
    void checkConnection();
};

#endif // NETWORKING_H
