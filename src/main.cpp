#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

// #include "wifi.hpp"
#include "defaults.hpp"
#include "radio.hpp"
#include "Config.hpp"
// #include "helpers.hpp"
#include "TrackingData.hpp"

TrackingData data(10);

Config conf;
Radio rf(&conf);

void setup () {
    /// Set up the built-in LED and turn it on to let the user know the ESP is working
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);

    /// Open up the serial monitor
    Serial.begin(115200);
    Serial.println();

    // Setup the radios according to the configuration
    rf.setup();

    Serial.println(ESP.getChipId());

    // If the pin is not pulled to ground read config or write the default one if its not
    if (digitalRead(RESET_CONF_PIN)) {
        Serial.println("Reading config from EEPROM");
        conf.read(0);
    } else {
        Serial.println("Saving default config to EEPROM");
        conf.write(0);
    }
}

void loop() {

    // Check for a WiFi connection and attempt to reestablish it if it died
    if (!rf.connected()) {
        digitalWrite(LED_PIN, LOW);
        if (!rf.connect()) {
            // Enter deep sleep in case the connection failed
            blink(); blink(); blink();
            Serial.println("Connection failed. Entering deep sleep mode...");
            ESP.deepSleep(conf.get<int>("wifiReconnectionInterval") * 1000, WAKE_NO_RFCAL);
        }
        digitalWrite(LED_PIN, HIGH);
    }

    // -- PROBLEM CHILD -- (comment this in and it rains multiple definitions of ledStatus (helpers.hpp))
    // /// Scan for networks and send the data to the FIND Server
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
