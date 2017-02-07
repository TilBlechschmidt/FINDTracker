#ifndef WIFI_H
#define WIFI_H

#include <ESP8266WiFi.h>
#include "const.hpp"

void connectWiFi() {
#ifdef DEBUG
    Serial.print("Connecting to ");
    Serial.print(SSID);
#endif

    WiFi.begin(SSID, PASSWORD);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
#ifdef DEBUG
        Serial.print(".");
#endif
    }

#ifdef DEBUG
    Serial.println();
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.println();
#endif
}

void watchWiFi() {
    if (WiFi.status() == WL_CONNECTED) {
        WiFi.softAPdisconnect(true);
    } else {
        WiFi.softAP("FIND Tracker", "12345678");
        // TODO: Launch configuration server (and create something to configurate..)
        connectWiFi();
    }
}

#endif
