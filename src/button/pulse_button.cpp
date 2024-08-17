#include <pulse_button.h>
#include <Arduino.h>
#include <pulse_logic.h>

#define BUTTON_PIN 4

unsigned long button_last_button_press_time = 0;

void button_setup() {
    pinMode(BUTTON_PIN, INPUT);
}

void button_tick() {
    int current_button_state = digitalRead(BUTTON_PIN);
    if (current_button_state == HIGH) {
		if (millis() - button_last_button_press_time > 50) {
			logic_button_pushed();
		}
		button_last_button_press_time = millis();
	}
}