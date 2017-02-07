#include <Arduino.h>
#include <ESP8266WiFi.h>

#include "wifi.hpp"
#include "const.hpp"
#include "helpers.hpp"
#include "tracking.hpp"

void setup () {
    /// Set up the built-in LED
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);

    /// Open up the serial monitor
    Serial.begin(115200);
    Serial.println();

    /// Set the ESP up for both client and station mode
    WiFi.mode(WIFI_AP_STA);
}

void loop() {
    /// Keep the WiFi connection online or open a configuration hotspot
    watchWiFi();

    /// Scan for networks and send the data to the FIND Server
    String trackingData = collectTrackingData();
    bool successful = sendTrackingData(trackingData);

    /// Blink to indicate that we have sent our location
    if (successful) blink();

    /// Clear a line for easier readability
    Serial.println();
}
