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
TrackingData data(conf, DEFAULT_BUFFER_SIZE);
ConfigServer cfgSrv(conf, 80);

WebSocketsServer webSocket(81);

void setup () {
    // Set up the EEPROM w/ a maximum size of 4096 bytes
    EEPROM.begin(4096);

    /// Set up the built-in LED and turn it on to let the user know the ESP is working
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);

    /// Open up the serial and TCP monitor
    Terminal::begin(115200);

    // If the pin is not pulled to ground read config or write the default one if its not
    if (digitalRead(RESET_CONF_PIN)) {
        conf->read(EEPROM_CONF_ADDR);
    } else {
        Terminal::println("Restoring factory settings...");
        conf->write(EEPROM_CONF_ADDR);
    }

    // Setup the radios according to the configuration
    rf.setup();

    // Setup the OTA server
    OTA();

    // Setup the websocket server
    webSocket.begin();
    // webSocket.onEvent(webSocketEvent);
}

void runServerHandlers() {
    ArduinoOTA.handle();
    cfgSrv.handle();
    Terminal::handle();
    webSocket.loop();
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
            Terminal::printf("Connection failed. Entering deep sleep mode for %dms ...\n", sleepTimeMS);
            ESP.deepSleep(sleepTimeMS * 1000, WAKE_NO_RFCAL);
        }
        digitalWrite(LED_PIN, HIGH);
    }

    // TODO: The data.send() step takes way too long
    if (conf->get<bool>("active")) {
        /// Update the environment data (scan for networks)
        if (data.update()) {
            // Send the data to the FIND Server
            String response = data.send();

            /// Blink to indicate that we have sent our location
            if (response != "") {
                blink();
                webSocket.broadcastTXT(response);
            }
        }
    }

    // Run all kinds of server handlers
    runServerHandlers();

    // Enter a very basic sleep mode and limit the amount of cycles to preserve power
    // (Turn off the radio and wake it up periodically to answer beacon signals from router)
    WiFi.setSleepMode(WIFI_MODEM_SLEEP);
    delay(1000);
}
