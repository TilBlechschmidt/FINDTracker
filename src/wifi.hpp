#ifndef WIFI_H
#define WIFI_H

#include <ESP8266WiFi.h>
#include "defaults.hpp"
#include "helpers.hpp"

void connectWiFi() {
    digitalWrite(LED_PIN, LOW);

#ifdef DEBUG
    Serial.print("Connecting to ");
    Serial.println(DEFAULT_SSID);
#endif

    WiFi.begin(DEFAULT_SSID, DEFAULT_PASSWORD);
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        // blink();
        blink();
        blink();
        Serial.println("Connection failed. Entering deep sleep mode...");
        return;
        // ESP.deepSleep(WIFI_RECON_INT * 1000, WAKE_NO_RFCAL);
    }

    OTA();

#ifdef DEBUG
    Serial.println();
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.println();
#endif

    digitalWrite(LED_PIN, HIGH);
}

void watchWiFi() {
    // Enable the hotspot if the pin is grounded
    if (digitalRead(HOTSPOT_PIN))
        WiFi.softAPdisconnect(true);
    else
        WiFi.softAP("FIND Tracker", "12345678"); // TODO: When this is actived once HTTP Post fails w/ conn refused

    if (!WiFi.isConnected())
        connectWiFi();
}

#endif
