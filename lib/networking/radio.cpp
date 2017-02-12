#include "radio.hpp"

bool Radio::connect() {
    String SSID = this->config->get<String>("SSID");
    String passphrase = this->config->get<String>("passphrase");

#ifdef DEBUG
    Serial.println("Connecting to " + SSID + " ...");
#endif

    WiFi.begin(SSID.c_str(), passphrase.c_str());
    if (WiFi.waitForConnectResult() != WL_CONNECTED)
        return false;

#ifdef DEBUG
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.println();
#endif

    return true;
}

bool Radio::connected() {
    return WiFi.isConnected();
}

void Radio::setup() {
    /// Set the ESP up for both client and station mode (aparently required for scanning)
    WiFi.mode(WIFI_AP_STA);

    // Set up an AP for configuration if tracking is inactive (factory setting)
    if (!this->config->get<bool>("active")) {
        char AP_SSID[25];
        sprintf(AP_SSID, "FIND Tracker %d", ESP.getChipId());
        WiFi.softAP(AP_SSID, AP_PASSPHRASE);
    } else {
        WiFi.softAPdisconnect(true);
    }
}
