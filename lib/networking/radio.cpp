#include "radio.hpp"

bool Radio::connect() {
    String hostname = this->config->get<String>("hostname");
    MDNS.begin(hostname.c_str());
    WiFi.hostname(hostname);

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
    Serial.println(" (" + this->config->get<String>("hostname") + ")");
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
    if (!this->config->get<bool>("active"))
        WiFi.softAP(("FIND Tracker " + String(ESP.getChipId())).c_str(), AP_PASSPHRASE);
    else
        WiFi.softAPdisconnect(true);
}
