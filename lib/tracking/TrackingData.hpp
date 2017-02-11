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
    TrackingData(int bufSize, Config* conf) : BSSIDBuffer(bufSize), RSSIBuffer(bufSize), config(conf) {}

    void initiateScan();
    bool update();
    String assemble();
    bool send();
};

#endif // TRACKING_DATA_H
