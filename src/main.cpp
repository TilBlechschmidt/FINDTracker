#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

#include "wifi.hpp"
#include "defaults.hpp"
#include "Config.hpp"
// #include "helpers.hpp"
// #include "TrackingData.hpp"

// TrackingData data(BUFFER_SIZE);

Config c;

void setup () {
    /// Set up the built-in LED and turn it on to let the user know the ESP is working
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);

    /// Open up the serial monitor
    Serial.begin(115200);
    Serial.println();

    /// Set the ESP up for both client and station mode (aparently required for scanning)
    WiFi.mode(WIFI_AP_STA);

    EEPROM.begin(4096);

    // StaticJsonBuffer<200> jsonBuffer;
    // JsonObject& root = jsonBuffer.createObject();
    // root["sensor"] = "gps";
    // root["time"] = 1351824120;
    //
    // String json;
    // root.printTo(json);
    // json += '\0';
    //
    // for(unsigned int i = 0; i < json.length(); i++) {
    //     Serial.print(json.charAt(i));
    //     EEPROM.write(i, json.charAt(i));
    //     // Serial.print(i);
    // }
    // // Serial.println();
    // // std::vector<char> chars(json.c_str(), json.c_str() + json.length() + 1u);
    //
    // // char test[10] = "abcdef";
    // // EEPROM.put(0, chars);
    // EEPROM.commit();
    //
    // delay(5000);
    // char currentChar;
    // String json2;
    // int cursor = 0;
    // while (currentChar != '\0') {
    //     currentChar = EEPROM.read(cursor);
    //     Serial.print(currentChar);
    //     json2 += currentChar;
    //     ++cursor;
    // }

    // char test2[10];
    // std::vector<char> chars2;
    // EEPROM.get(0, chars2);
    // std::string str(chars2.begin(), chars2.end());
    // Serial.println(str.c_str());

    // EEPROM.write(0, 121);
    // EEPROM.commit();
    // delay(5000);
    // Serial.print(EEPROM.read(0), DEC);
    // Serial.println();

    // If the pin is not pulled to ground read config
    if (digitalRead(RESET_CONF_PIN)) {
        Serial.println("Reading config from EEPROM");
        c.read(0);
    } else {
        Serial.println("Saving default config to EEPROM");
        c.write(0);
    }
}

void loop() {
    /// Keep the WiFi connection online or open a configuration hotspot
    watchWiFi();

    /// Scan for networks and send the data to the FIND Server
    // data.update();
    // bool successful = data.send();
    //
    // /// Blink to indicate that we have sent our location
    // if (successful)
    //     blink();

    ArduinoOTA.handle();

    // WiFi.setSleepMode(WIFI_MODEM_SLEEP);
    // delay(10000);
}
