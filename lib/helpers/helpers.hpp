#ifndef FIND_HELPERS_H
#define FIND_HELPERS_H

#include <Arduino.h>
#include <ArduinoOTA.h>
#include <ESP8266mDNS.h>
#include <vector>
#include <Ticker.h>

#include "defaults.hpp"

void blink();
void blinkSync();
void OTA();

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
