#include "radio.hpp"

bool Radio::connect() {
    String hostname = this->config->get<String>("hostname");

    String SSID = this->config->get<String>("SSID");
    String passphrase = this->config->get<String>("passphrase");

#ifdef DEBUG
    Terminal::println("Connecting to " + SSID + " ...");
#endif

    WiFi.begin(SSID.c_str(), passphrase.c_str());
    if (WiFi.waitForConnectResult() != WL_CONNECTED)
        return false;

#ifdef DEBUG
    Terminal::print("IP address: ");
    Terminal::println(WiFi.localIP().toString());
    Terminal::println(" (" + this->config->get<String>("hostname") + ")");
#endif

    return true;
}

bool Radio::connected() {
    return WiFi.isConnected();
}

IPAddress apIP(10, 10, 10, 1);

void Radio::setup() {
    /// Set the ESP up for both client and station mode (aparently required for scanning)
    WiFi.mode(WIFI_AP_STA);

    // Set up an AP for configuration if tracking is inactive (factory setting)
    if (!this->config->get<bool>("active")) {
        WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
        WiFi.softAP(("FIND Tracker " + String(ESP.getChipId())).c_str(), this->config->get<String>("auth").c_str());
    } else
        WiFi.softAPdisconnect(true);
}
