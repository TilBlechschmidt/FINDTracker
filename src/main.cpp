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

// Test functions for remote debugging
// int vasprintf(char** strp, const char* fmt, va_list ap) {
//     va_list ap2;
//     va_copy(ap2, ap);
//     char tmp[1];
//     int size = vsnprintf(tmp, 1, fmt, ap2);
//     if (size <= 0) return size;
//     va_end(ap2);
//     size += 1;
//     *strp = (char*)malloc(size * sizeof(char));
//     return vsnprintf(*strp, size, fmt, ap);
// }
//
// void pline(char* str, ...) {
// 	char* buf;
// 	va_list args;
//
// 	va_start(args, str);
// 	vasprintf(&buf, str, args);
// 	va_end(args);
//
// 	Terminal::println(buf);
// }
// End of test functions

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
        conf->read(0);
    } else {
        Terminal::println("Restoring factory settings...");
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
    Terminal::handle();
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
            bool successful = data.send();

            /// Blink to indicate that we have sent our location
            if (successful) blink();
        }
    }

    // Run all kinds of server handlers
    runServerHandlers();

    // Enter a very basic sleep mode and limit the amount of cycles to preserve power
    // (Turn off the radio and wake it up periodically to answer beacon signals from router)
    WiFi.setSleepMode(WIFI_MODEM_SLEEP);
    delay(1000);
}
