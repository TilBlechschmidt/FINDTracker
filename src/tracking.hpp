#ifndef TRACKING_H
#define TRACKING_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include "const.hpp"

bool sendTrackingData(String data) {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin(FIND_SERVER_URL);

        http.addHeader("Content-Type", "application/json");
        http.addHeader("cache-control", "no-cache");

        int httpCode = http.POST(data);
        String payload = http.getString();

        http.end();

        if (httpCode >= 200 && httpCode < 300) {
#ifdef DEBUG
            Serial.println(payload);
#endif
          return true;
        } else {
            Serial.printf("HTTP POST failed with code %d\n", httpCode);
            Serial.println(http.errorToString(httpCode));
        }

    } else {
        Serial.println("Couldn't send request since there's no WiFi connection");
    }

    return false;
}

String collectTrackingData() {
    /// Initiate a scan for networks
    int networkCount = WiFi.scanNetworks(false, true);

    /// Create the JSON object
    DynamicJsonBuffer  jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();

    /// Set the metadata
    root["group"] = FIND_GROUP;
    root["username"] = FIND_USER;

    /// Create the array containing the fingerprints
    JsonArray& fingerprints = root.createNestedArray("wifi-fingerprint");

    /// Iterate over the networks
    for (int i = 0; i < networkCount; i++) {
        /// Create a JSON object for the networks fingerprint
        StaticJsonBuffer<200> fingerprintBuffer;
        JsonObject& fingerprint = fingerprintBuffer.createObject();

        /// Set the properties of the fingerprint
        fingerprint["mac"] = WiFi.BSSIDstr(i);
        fingerprint["rssi"] = WiFi.RSSI(i);

        /// Add the fingerprint
        fingerprints.add(fingerprint);
    }

    /// Convert it into a valid JSON string
    String trackingData;
    root.printTo(trackingData);

    /// Return the tracking data we collected
    return trackingData;
}

#endif
