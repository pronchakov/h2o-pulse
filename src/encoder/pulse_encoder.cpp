#include <pulse_encoder.h>
#include <Arduino.h>
#include <Encoder.h>
#include <pulse_logic.h>

#define ENCODER_INTERRUPT_PIN_1 2
#define ENCODER_INTERRUPT_PIN_2 3
#define ENCODER_BUTTON_PIN 6

Encoder enc(ENCODER_INTERRUPT_PIN_1, ENCODER_INTERRUPT_PIN_2); 
unsigned long encoder_last_button_press_time = 0;

void encoder_setup() {
  pinMode(ENCODER_BUTTON_PIN, INPUT_PULLUP);
}

void encoder_tick() {
  int read_value = enc.read();
  if (read_value != 0) {
    if (read_value >= 4) {
        logic_increment_value();
        enc.write(0);
    }
    if (read_value <= -4) {
        logic_decrement_value();
        enc.write(0);
    }
  }

  int current_button_state = digitalRead(ENCODER_BUTTON_PIN);
  if (current_button_state == LOW) {
		if (millis() - encoder_last_button_press_time > 50) {
			logic_change_type();
		}
		encoder_last_button_press_time = millis();
	}

} 