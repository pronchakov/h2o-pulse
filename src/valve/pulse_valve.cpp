#include <Arduino.h>
#include <pulse_valve.h>

#define VALVE_PIN 5

void valve_setup() {
    pinMode(VALVE_PIN, OUTPUT);
    digitalWrite(VALVE_PIN, HIGH);
}

void valve_open() {
    digitalWrite(VALVE_PIN, LOW);
}

void valve_close() {
    digitalWrite(VALVE_PIN, HIGH);
}