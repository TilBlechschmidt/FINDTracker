#ifndef TRACKING_DATA_H
#define TRACKING_DATA_H

#include <algorithm>
#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WebSocketsServer.h>
#include <Hash.h>

#include "defaults.hpp"
#include "helpers.hpp"
#include "Config.hpp"

class TrackingData {
    CircularBuffer<std::vector<String>> BSSIDBuffer;
    CircularBuffer<std::vector<int32_t>> RSSIBuffer;
    Config* config;

    WiFiUDP udpSock;

    void sendSMPStateUpdate(String data);

public:
    TrackingData(Config* conf, int bufSize) : config(conf), BSSIDBuffer(bufSize), RSSIBuffer(bufSize) {}

    void initiateScan();
    bool update();
    String assemble();
    String send();
};

#endif // TRACKING_DATA_H
