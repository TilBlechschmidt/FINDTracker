#include "Config.hpp"

Config::Config() {
    // this->data.data = {
    //     DEFAULT_WIFI_RECON_INT,
    //     DEFAULT_SSID,
    //     DEFAULT_PASSWORD,
    //
    //     DEFAULT_ACTIVE,
    //     DEFAULT_BUFFER_SIZE,
    //
    //     DEFAULT_TRACKING_URL,
    //     DEFAULT_TRACKING_GROUP,
    //     DEFAULT_TRACKING_USER
    // };
    this->data.data["wifiReconnectionInterval"] = DEFAULT_WIFI_RECON_INT;
    this->data.data["SSID"] = DEFAULT_SSID;
    this->data.data["passphrase"] = DEFAULT_PASSWORD;

    this->data.data["active"] = DEFAULT_ACTIVE;
    this->data.data["bufferSize"] = DEFAULT_BUFFER_SIZE;

    this->data.data["trackingURL"] = DEFAULT_TRACKING_URL;
    this->data.data["trackingGroup"] = DEFAULT_TRACKING_GROUP;
    this->data.data["trackingUser"] = DEFAULT_TRACKING_USER;

}

void Config::read(int address) {
    char currentChar;
    String json;
    int cursor = 0;
    while (currentChar != '\0') {
        currentChar = EEPROM.read(cursor++);
        json += currentChar;
    }

    DynamicJsonBuffer buf;
    JsonObject& dat = buf.parseObject(json);
    // TODO: Write this into the ConfigData struct
    // this->data = ConfigData(dat);
}

void Config::write(int addr) {
    String json;
    this->data.data.printTo(json);
    json += '\0';

    for(unsigned int i = 0; i < json.length(); i++)
        EEPROM.write(i, json.charAt(i));

    // EEPROM.commit();

    // delay(5000);

    this->read(addr);
}
