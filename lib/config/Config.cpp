#include "Config.hpp"

Config::Config() : data(dataBuffer.createObject()) {
    this->data["auth"] = DEFAULT_AUTH;

    this->data["wifiReconnectionInterval"] = DEFAULT_WIFI_RECON_INT;
    this->data["SSID"] = DEFAULT_SSID;
    this->data["passphrase"] = DEFAULT_PASSPHRASE;
    this->data["hostname"] = DEFAULT_HOSTNAME;

    this->data["active"] = DEFAULT_ACTIVE;
    this->data["bufferSize"] = DEFAULT_BUFFER_SIZE;

    this->data["trackingURL"] = DEFAULT_TRACKING_URL;
    this->data["trackingGroup"] = DEFAULT_TRACKING_GROUP;
    this->data["trackingUser"] = DEFAULT_TRACKING_USER;
}

void Config::readFromString(String str) {
    String json = this->dataBuffer.strdup(str);
    JsonObject& parsed = this->dataBuffer.parseObject(json);

    for(JsonObject::iterator it=parsed.begin(); it!=parsed.end(); ++it)
        this->data[it->key] = it->value;
}

void Config::read(int address) {
    char currentChar;
    String json;
    int cursor = 0;
    while (currentChar != '\0') {
        currentChar = EEPROM.read(cursor++);
        json += currentChar;
    }

    this->readFromString(json);
}

void Config::write(int addr) {
    String json;
    this->data.printTo(json);
    json += '\0';

    for(unsigned int i = 0; i < json.length(); i++)
        EEPROM.write(i, json.charAt(i));

    EEPROM.commit();
}
