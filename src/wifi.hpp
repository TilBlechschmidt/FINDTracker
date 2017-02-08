#ifndef WIFI_H
#define WIFI_H

#include <ESP8266WiFi.h>
#include "const.hpp"
#include "helpers.hpp"

void connectWiFi() {
    digitalWrite(LED_PIN, LOW);

#ifdef DEBUG
    Serial.print("Connecting to ");
    Serial.println(SSID);
#endif

    WiFi.begin(SSID, PASSWORD);
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        blink();
        blink();
        blink();
        Serial.println("Connection failed. Entering deep sleep mode...");
        ESP.deepSleep(WIFI_RECON_INT * 1000, WAKE_NO_RFCAL);
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
    if (WiFi.status() == WL_CONNECTED) {
        WiFi.softAPdisconnect(true); // TODO: Check a GPIO Pin to be HIGH in order to do this (preserving power in everyday use)
    } else {
        WiFi.softAP("FIND Tracker", "12345678");
        // TODO: Launch configuration server (and create something to configurate..)
        connectWiFi();
    }
}

#endif
