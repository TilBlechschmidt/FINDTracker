#include "TrackingData.hpp"

IPAddress smpIP(224, 0, 0, 1);
unsigned int remotePort = 1337;

void TrackingData::initiateScan() {
    WiFi.scanNetworks(true, true);
}

bool TrackingData::update() {
    int status = WiFi.scanComplete();

    if (status == WIFI_SCAN_RUNNING) return false;

    if (status == -2) {  // No scan initiated previously
        this->initiateScan();
        return false;
    }

    /// If there was a previous scan and the scan is not running the status equals the number of networks discovered
    // int networkCount = status;

    // Create a list of fingerprints
    std::vector<String> BSSIDs;
    std::vector<int32_t> RSSIs;

    /// Iterate over the networks and populate the list
    for (int i = 0; i < status; ++i) {
        BSSIDs.push_back(WiFi.BSSIDstr(i));
        RSSIs.push_back(WiFi.RSSI(i));
    }

    /// Add the fingerprints to the circular buffer
    (this->BSSIDBuffer).push(BSSIDs);
    (this->RSSIBuffer).push(RSSIs);

    // Initiate a new scan
    this->initiateScan();

    return true;
}

String TrackingData::assemble() {
    /// Create the JSON object
    DynamicJsonBuffer  jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();

    /// Set the metadata
    root["group"] = this->config->get<String>("trackingGroup");
    root["username"] = this->config->get<String>("trackingUser");

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
        for (unsigned int network = 0; network < BSSIDHistory[timeDelta].size(); ++network) {
            BSSID = BSSIDHistory[timeDelta][network];
            RSSI = RSSIHistory[timeDelta][network];

            // Only push the fingerprint if we haven't encountered it yet
            if (std::find(updatedBSSIDs.begin(), updatedBSSIDs.end(), BSSID) == updatedBSSIDs.end()) {
                /// Add fingerprint to final tracking data
                JsonObject& fp = jsonBuffer.createObject();

                /// Set the properties of the fingerprint
                fp["mac"] = BSSID;
                fp["rssi"] = RSSI;
                tdFingerprints.add(fp);

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

void TrackingData::sendSMPStateUpdate(String data) {
    DynamicJsonBuffer buf;
    JsonObject& location = buf.parseObject(data);
    JsonObject& payload = buf.createObject();
    payload["location"] = location["location"];
    payload["user"] = this->config->get<String>("trackingUser");

    JsonObject& response = buf.createObject();
    response["action"] = "stateUpdate";
    response["payload"] = payload;

    String datagram;
    response.printTo(datagram);

    // TODO Handle network reconnects
    this->udpSock.begin(1337);
    this->udpSock.beginMulticast(IPAddress(0, 0, 0, 0), IPAddress(224, 0, 0, 1), 1337);
    this->udpSock.beginPacket(smpIP, remotePort);
    for (int i = 0; i < datagram.length(); ++i) this->udpSock.write(datagram.charAt(i));
    this->udpSock.endPacket();
}

bool TrackingData::send() {
    if (WiFi.status() == WL_CONNECTED) {
        // TODO: Use async TCP, open a pipe and keep it open just sending new requests
        HTTPClient http;
        http.begin("http://" + this->config->get<String>("trackingHost") + "/track");

        http.addHeader("Content-Type", "application/json");
        http.addHeader("cache-control", "no-cache");

        int httpCode = http.POST(this->assemble());
        String payload = http.getString();

        http.end();

        if (httpCode >= 200 && httpCode < 300) {
#ifdef DEBUG
            Terminal::println(payload);
#endif
            this->sendSMPStateUpdate(payload);
            return true;
        } else {
            Terminal::printf("HTTP POST failed with code %d\n", httpCode);
            Terminal::println(http.errorToString(httpCode));
        }

    } else {
        Terminal::println("Couldn't send request since there's no WiFi connection");
    }

    return false;
}
