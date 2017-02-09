#ifndef FIND_HELPERS_H
#define FIND_HELPERS_H

#include <Arduino.h>
#include <ArduinoOTA.h>
#include <ESP8266mDNS.h>
#include <vector>
#include <Ticker.h>

#include "defaults.hpp"

void blink() {
    digitalWrite(LED_PIN, LOW);
    delay(75);
    digitalWrite(LED_PIN, HIGH);
    delay(75);
}

uint8_t ledStatus;
void blinkSync() {
    if (ledStatus)
        digitalWrite(LED_PIN, HIGH);
    else
        digitalWrite(LED_PIN, LOW);
    ledStatus = (ledStatus + 1) % 2; // Flip ledStatus

}

Ticker blinker; // Ticker object called blinker.

void OTA() {
    // Port defaults to 8266
    // ArduinoOTA.setPort(8266);

    // Hostname defaults to esp8266-[ChipID]
    // ArduinoOTA.setHostname("myesp8266");

    // No authentication by default
    // ArduinoOTA.setPassword("admin");

    // Password can be set with it's md5 value as well
    // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
    // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

    ArduinoOTA.onStart([]() {
        String type;
        // if (ArduinoOTA.getCommand() == U_FLASH)
            type = "sketch";
        // else // U_SPIFFS
            // type = "filesystem";

        // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
        Serial.println("Start updating " + type);
        blinker.attach(0.05, blinkSync);
    });
    ArduinoOTA.onEnd([]() {
        blinker.detach();
        Serial.println("\nEnd");
    });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    });
    ArduinoOTA.onError([](ota_error_t error) {
        blinker.detach();
        Serial.printf("Error[%u]: ", error);
        if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
        else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
        else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
        else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
        else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });
    ArduinoOTA.begin();
}

template<typename T>
class CircularBuffer {
    int size;
    int index;
    int pushCount;

public:
    std::vector<T> buffer;
    void push(T element) {
        (this->buffer)[index] = element;

        ++(this->pushCount);

        if (this->index == size - 1) this->index = 0;
        else ++(this->index);
    }

    void clear() {
        this->buffer.clear();
    }

    std::vector<T> get() {
        std::vector<T> elements;
        int cursor;

        elements.reserve(this->pushCount);
        cursor = this->index;
        do {
            if (!((this->pushCount) < (this->size) && cursor >= (this->pushCount)))
                elements.push_back((this->buffer)[cursor]);

            if (cursor >= (this->size - 1)) cursor = 0;
            else cursor++;
        } while(cursor != index);

        return elements;
    }

    CircularBuffer(int size) : buffer(size) {
        this->size = size;
        this->buffer.reserve(size);
        this->pushCount = 0;
        this->index = 0;
    }
};


#endif
