#include <Arduino.h>

#include <pulse_button.h>
#include <pulse_encoder.h>
#include <pulse_display.h>
#include <pulse_valve.h>
#include <pulse_logic.h>

void setup() {
    Serial.begin(9600);

    button_setup();
    encoder_setup();
    display_setup();
    valve_setup();
    logic_setup();
}

void loop() {
    encoder_tick();
    button_tick();
    logic_tick();
}