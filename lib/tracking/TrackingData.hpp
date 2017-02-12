#ifndef TRACKING_DATA_H
#define TRACKING_DATA_H

#include <algorithm>
#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include "defaults.hpp"
#include "helpers.hpp"
#include "Config.hpp"

class TrackingData {
    CircularBuffer<std::vector<String>> BSSIDBuffer;
    CircularBuffer<std::vector<int32_t>> RSSIBuffer;
    Config* config;

public:
    TrackingData(Config* conf, int bufSize) : config(conf), BSSIDBuffer(bufSize), RSSIBuffer(bufSize) {
        Serial.printf("Tracking config pointer: %p\n", conf);
        Serial.println("Value: " + conf->get<String>("trackingURL"));
        Serial.println("Value2: " + this->config->get<String>("trackingURL"));
    }

    void initiateScan();
    bool update();
    String assemble();
    bool send();
};

#endif // TRACKING_DATA_H
