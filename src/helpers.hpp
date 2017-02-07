#ifndef HELPERS_H
#define HELPERS_H

#include <Arduino.h>

void blink() {
    digitalWrite(LED_PIN, LOW);
    delay(75);
    digitalWrite(LED_PIN, HIGH);
}

#endif
