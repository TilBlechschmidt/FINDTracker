#ifndef HELPERS_H
#define HELPERS_H

#include <Arduino.h>
#include <vector>

#include "const.hpp"

void blink() {
    digitalWrite(LED_PIN, LOW);
    delay(75);
    digitalWrite(LED_PIN, HIGH);
}

template<typename T>
class CircularBuffer {
    int size;
    int index;

public:
    std::vector<T> buffer;
    void push(T element) {
        (this->buffer)[index] = element;

        if (this->index == size - 1) this->index = 0;
        else ++(this->index);
    }

    void clear() {
        this->buffer.clear();
    }

    std::vector<T> get() {
        std::vector<T> elements;
        int cursor;

        for (int i = 0; i < size; ++i) {
            cursor = index + i;
            if (i >= size - 2) cursor = cursor - size;
            elements.push_back((this->buffer)[cursor]);
        }

        return elements;
    }

    CircularBuffer(int size) {
        this->size = size;
        this->buffer.reserve(size);
    }
};


#endif
