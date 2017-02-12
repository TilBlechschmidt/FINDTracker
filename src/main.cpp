#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

#include "helpers.hpp"
#include "defaults.hpp"
#include "radio.hpp"
#include "Config.hpp"
#include "TrackingData.hpp"
#include "ConfigServer.hpp"


Config* conf = new Config();
Radio rf(conf);
TrackingData data(conf, 10);
ConfigServer cfgSrv(80);

void setup () {
    // Set up the EEPROM w/ a maximum size of 4096 bytes
    EEPROM.begin(4096);

    /// Set up the built-in LED and turn it on to let the user know the ESP is working
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);

    /// Open up the serial monitor
    Serial.begin(115200);
    Serial.println();

    // If the pin is not pulled to ground read config or write the default one if its not
    if (digitalRead(RESET_CONF_PIN)) {
        Serial.println("Reading config from EEPROM");
        conf->read(0);
    } else {
        Serial.println("Saving default config to EEPROM");
        conf->write(0);
    }

    // Setup the radios according to the configuration
    rf.setup();

    // Setup the OTA server
    OTA();
}

void runServerHandlers() {
    ArduinoOTA.handle();
    cfgSrv.handle();
}

int sleepTimeMS;
void loop() {
    // Check for a WiFi connection and attempt to reestablish it if it died
    if (!rf.connected()) {
        digitalWrite(LED_PIN, LOW);
        if (!rf.connect()) {
            // Enter deep sleep in case the connection failed
            sleepTimeMS = conf->get<int>("wifiReconnectionInterval");
            blink(); blink(); blink();
            Serial.printf("Connection failed. Entering deep sleep mode for %dms ...\n", sleepTimeMS);
            ESP.deepSleep(sleepTimeMS * 1000, WAKE_NO_RFCAL);
        }
        digitalWrite(LED_PIN, HIGH);
    }

    // TODO: The data.update() step takes way too long
    if (conf->get<bool>("active")) {
        /// Update the environment data (scan for networks)
        if (data.update()) {
            // Send the data to the FIND Server
            bool successful = data.send();

            /// Blink to indicate that we have sent our location
            if (successful)
                blink();
        }
    }

    // Run all kinds of server handlers
    runServerHandlers();

    // WiFi.setSleepMode(WIFI_MODEM_SLEEP);
    // delay(10000);
}
