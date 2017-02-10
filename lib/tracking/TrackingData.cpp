#include "TrackingData.hpp"

void TrackingData::update() {
    /// Initiate a scan for networks TODO: Run async
    int networkCount = WiFi.scanNetworks(false, true);

    // Create a list of fingerprints
    std::vector<String> BSSIDs;
    std::vector<int32_t> RSSIs;

    /// Iterate over the networks and populate the list
    for (int i = 0; i < networkCount; ++i) {
        BSSIDs.push_back(WiFi.BSSIDstr(i));
        RSSIs.push_back(WiFi.RSSI(i));
    }

    /// Add the fingerprints to the circular buffer
    (this->BSSIDBuffer).push(BSSIDs);
    (this->RSSIBuffer).push(RSSIs);
}

String TrackingData::assemble() {
    /// Create the JSON object
    DynamicJsonBuffer  jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();

    /// Set the metadata
    root["group"] = FIND_GROUP;
    root["username"] = FIND_USER;

    /// Create the array containing the fingerprints
    JsonArray& tdFingerprints = root.createNestedArray("wifi-fingerprint");

    std::vector<std::vector<String>> BSSIDHistory = (this->BSSIDBuffer).get();
    std::vector<std::vector<int32_t>> RSSIHistory = (this->RSSIBuffer).get();
    std::vector<String> updatedBSSIDs;

    String BSSID;
    int32_t RSSI;

    /// Iterate over fingerprintsHistory in reverse to keep the newest values
    for (unsigned timeDelta = BSSIDHistory.size(); timeDelta-- > 0; ) {
        /// Iterate over every fingerprint in each timeframe of the history
        // for (Fingerprint fingerprint : fingerprintsHistory[i]) {
        for (unsigned int network = 0; network < BSSIDHistory[timeDelta].size(); ++network) {
            BSSID = BSSIDHistory[timeDelta][network];
            RSSI = RSSIHistory[timeDelta][network];

            // Only push the fingerprint if we haven't encountered it yet
            if (std::find(updatedBSSIDs.begin(), updatedBSSIDs.end(), BSSID) == updatedBSSIDs.end()) {
                /// Add fingerprint to final tracking data
                StaticJsonBuffer<200> fingerprintBuffer;
                JsonObject& fp = fingerprintBuffer.createObject();

                /// Set the properties of the fingerprint
                fp["mac"] = BSSID;
                fp["rssi"] = RSSI;
                tdFingerprints.add(fp);
                // tdFingerprints.add(fingerprint.toJSON());

                /// Save the BSSID of the fingerprint to prevent duplicates
                updatedBSSIDs.push_back(BSSID);
            }
        }
    }

    /// Convert it into a valid JSON string
    String td;
    root.printTo(td);

    /// Return the tracking data we collected
    return td;
}

bool TrackingData::send() {
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
