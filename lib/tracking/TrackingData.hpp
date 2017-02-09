#ifndef TRACKING_DATA_H
#define TRACKING_DATA_H

#include <algorithm>
#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include "defaults.hpp"
#include "helpers.hpp"

class TrackingData {
    CircularBuffer<std::vector<String>> BSSIDBuffer;
    CircularBuffer<std::vector<int32_t>> RSSIBuffer;

public:
    TrackingData(int bufSize) : BSSIDBuffer(bufSize), RSSIBuffer(bufSize) {}

    void update();

    String assemble();

    bool send();
};

#endif // TRACKING_DATA_H
