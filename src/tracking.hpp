#ifndef TRACKING_H
#define TRACKING_H

#include <algorithm>
#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include "const.hpp"

class Fingerprint {
public:
    String BSSID;
    int32_t RSSI;

    Fingerprint(String BSSID, int32_t RSSI) {
        this->BSSID = BSSID;
        this->RSSI = RSSI;
    }

    JsonObject& toJSON() {
        /// Create a JSON object for the networks fingerprint
        StaticJsonBuffer<200> fingerprintBuffer;
        JsonObject& fingerprint = fingerprintBuffer.createObject();

        /// Set the properties of the fingerprint
        fingerprint["mac"] = this->BSSID;
        fingerprint["rssi"] = this->RSSI;

        return fingerprint;
    }
};

class TrackingData {
    CircularBuffer<std::vector<Fingerprint>> fingerprintsBuffer;

public:
    TrackingData() : fingerprintsBuffer(BUFFER_SIZE) {}

    void update() {
        /// Initiate a scan for networks
        int networkCount = WiFi.scanNetworks(false, true);

        // Create a list of fingerprints
        std::vector<Fingerprint> fingerprints;

        /// Iterate over the networks and populate the list
        for (int i = 0; i < networkCount; i++) {
            fingerprints.push_back(
                Fingerprint(WiFi.BSSIDstr(i), WiFi.RSSI(i))
            );
        }

        /// Add the fingerprints to the circular buffer
        (this->fingerprintsBuffer).push(fingerprints);
    }

    String assemble() {
        /// Create the JSON object
        DynamicJsonBuffer  jsonBuffer;
        JsonObject& root = jsonBuffer.createObject();

        /// Set the metadata
        root["group"] = FIND_GROUP;
        root["username"] = FIND_USER;

        /// Create the array containing the fingerprints
        JsonArray& tdFingerprints = root.createNestedArray("wifi-fingerprint");

        std::vector<std::vector<Fingerprint>> fingerprintsHistory = (this->fingerprintsBuffer).get();
        std::vector<String> updatedBSSIDs;

        /// Iterate over fingerprintsHistory in reverse to keep the newest values
        for (unsigned i = fingerprintsHistory.size(); i-- > 0; ) {
            /// Iterate over every fingerprint in each timeframe of the history
            for (Fingerprint fingerprint : fingerprintsHistory[i]) {

                // Only push the fingerprint if we haven't encountered it yet
                if (std::find(updatedBSSIDs.begin(), updatedBSSIDs.end(), fingerprint.BSSID) == updatedBSSIDs.end()) {
                    /// Add fingerprint to final tracking data
                    StaticJsonBuffer<200> fingerprintBuffer;
                    JsonObject& fp = fingerprintBuffer.createObject();

                    /// Set the properties of the fingerprint
                    fp["mac"] = fingerprint.BSSID;
                    fp["rssi"] = fingerprint.RSSI;
                    tdFingerprints.add(fp);
                    // tdFingerprints.add(fingerprint.toJSON());

                    /// Save the BSSID of the fingerprint to prevent duplicates
                    updatedBSSIDs.push_back(fingerprint.BSSID);
                }
            }
        }

        /// Convert it into a valid JSON string
        String td;
        root.printTo(td);

        /// Return the tracking data we collected
        return td;
    }

    bool send() {
        if (WiFi.status() == WL_CONNECTED) {
            HTTPClient http;
            http.begin(FIND_SERVER_URL);

            http.addHeader("Content-Type", "application/json");
            http.addHeader("cache-control", "no-cache");

            int httpCode = http.POST(this->assemble());
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
};

#endif
