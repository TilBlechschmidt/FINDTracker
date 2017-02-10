#include "Config.hpp"

Config::Config() {
    EEPROM.begin(4096);

    JsonObject* json = this->data.data;
    (*json)["wifiReconnectionInterval"] = DEFAULT_WIFI_RECON_INT;
    (*json)["SSID"] = DEFAULT_SSID;
    (*json)["passphrase"] = DEFAULT_PASSPHRASE;

    (*json)["active"] = DEFAULT_ACTIVE;
    (*json)["bufferSize"] = DEFAULT_BUFFER_SIZE;

    (*json)["trackingURL"] = DEFAULT_TRACKING_URL;
    (*json)["trackingGroup"] = DEFAULT_TRACKING_GROUP;
    (*json)["trackingUser"] = DEFAULT_TRACKING_USER;
}

void Config::read(int address) {
    char currentChar;
    String json;
    int cursor = 0;
    while (currentChar != '\0') {
        currentChar = EEPROM.read(cursor++);
        json += currentChar;
    }

    ConfigData newConfig;
    JsonObject* dat = &newConfig.dataBuffer.parseObject(json);

    newConfig.data = dat;
    this->data = newConfig;
}

void Config::write(int addr) {
    String json;
    (*(this->data.data)).printTo(json);
    json += '\0';

    for(unsigned int i = 0; i < json.length(); i++)
        EEPROM.write(i, json.charAt(i));
}
