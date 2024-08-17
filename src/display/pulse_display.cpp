#include <pulse_display.h>
#include <LedControl.h>
#include <pulse_logic.h>

#define DISPLAY_DATA_PIN 12
#define DISPLAY_CLOCK_PIN 11
#define DISPLAY_CS_PIN 10

#define DISPLAY_COUNT 1
#define DISPLAY_ADDRESS 0

#define DISPLAY_DIGIT_0 0
#define DISPLAY_DIGIT_1 1
#define DISPLAY_DIGIT_2 2
#define DISPLAY_DIGIT_3 3
#define DISPLAY_DIGIT_4 4
#define DISPLAY_DIGIT_5 5
#define DISPLAY_DIGIT_6 6
#define DISPLAY_DIGIT_7 7

#define DISPLAY_LETTER_U B00111110
#define DISPLAY_LETTER_O B01111110
#define DISPLAY_LETTER_L B10001110

#define DISPLAY_LETTER_S B01011011
#define DISPLAY_LETTER_E B01001111
#define DISPLAY_LETTER_C B11001110

// #define DISPLAY_LETTER_C B11001110

// #define DISPLAY_LETTER_V B01111111
// #define DISPLAY_LETTER_R B01100111
// #define DISPLAY_LETTER_E B11001111
// #define DISPLAY_LETTER_M B01110110

// #define DISPLAY_LETTER_O B01111110
// #define DISPLAY_LETTER_B B01011111
// #define DISPLAY_LETTER_HARD B10011111

//            _B01000000
// B00000010 |_| B00100000    _B00000001
// B00000100 |_| B00010000              .B10000000
//             B00001000

LedControl lc=LedControl(DISPLAY_DATA_PIN, DISPLAY_CLOCK_PIN, DISPLAY_CS_PIN, DISPLAY_COUNT);
int display_spinner_current = 0;
byte display_spinner[] {
    B01000000,
    B00100000,
    B00010000,
    B00001000,
    B00000100,
    B00000010,
};

void display_setup() {
    lc.setIntensity(0, 4);
    lc.clearDisplay(0);
    lc.shutdown(0, false);
}

void display_show_value(ParamType type, int value) {
    if (value < 0) {
        return;
    }

    lc.setRow(DISPLAY_ADDRESS, DISPLAY_DIGIT_0, B00000000);
    lc.setRow(DISPLAY_ADDRESS, DISPLAY_DIGIT_1, B00000000);
    lc.setRow(DISPLAY_ADDRESS, DISPLAY_DIGIT_2, B00000000);
    lc.setRow(DISPLAY_ADDRESS, DISPLAY_DIGIT_3, B00000000);

    int units;
    int tens;
    int houndrads;
    int thousands;

    thousands = value / 1000;
    value -= thousands * 1000;
    
    houndrads = value / 100;
    value -= houndrads * 100;

    tens = value / 10;
    value -= tens * 10;

    units = value;

    switch (type) {
        case Time:
            lc.setDigit(DISPLAY_ADDRESS, DISPLAY_DIGIT_0, (byte)units, false);
            if (thousands > 0 || houndrads > 0 || tens > 0) {lc.setDigit(DISPLAY_ADDRESS, DISPLAY_DIGIT_1, (byte)tens, false);}
            if (thousands > 0 || houndrads > 0) {lc.setDigit(DISPLAY_ADDRESS, DISPLAY_DIGIT_2, (byte)houndrads, false);}
            if (thousands > 0) {lc.setDigit(DISPLAY_ADDRESS, DISPLAY_DIGIT_3, (byte)thousands, false);}
            break;
        case Volume:
            lc.setDigit(DISPLAY_ADDRESS, DISPLAY_DIGIT_0, (byte)units, false);
            lc.setDigit(DISPLAY_ADDRESS, DISPLAY_DIGIT_1, (byte)tens, false);
            lc.setDigit(DISPLAY_ADDRESS, DISPLAY_DIGIT_2, (byte)houndrads, false);
            lc.setDigit(DISPLAY_ADDRESS, DISPLAY_DIGIT_3, (byte)thousands, true);
            break;
    }

    
}

void display_show_type(ParamType type) {
    switch (type) {
        case Time: 
            lc.setRow(DISPLAY_ADDRESS, DISPLAY_DIGIT_7, DISPLAY_LETTER_S); 
            lc.setRow(DISPLAY_ADDRESS, DISPLAY_DIGIT_6, DISPLAY_LETTER_E); 
            lc.setRow(DISPLAY_ADDRESS, DISPLAY_DIGIT_5, DISPLAY_LETTER_C); 
            break;
        case Volume:
            lc.setRow(DISPLAY_ADDRESS, DISPLAY_DIGIT_7, DISPLAY_LETTER_U); 
            lc.setRow(DISPLAY_ADDRESS, DISPLAY_DIGIT_6, DISPLAY_LETTER_O); 
            lc.setRow(DISPLAY_ADDRESS, DISPLAY_DIGIT_5, DISPLAY_LETTER_L); 
            break;
    };
}

void display_move_spinner() {
    lc.setRow(DISPLAY_ADDRESS, DISPLAY_DIGIT_0, display_spinner[display_spinner_current]);
    display_spinner_current++;
    if (display_spinner_current == (sizeof(display_spinner) / sizeof(byte))) {
        display_spinner_current = 0;
    }
}

void display_clear_spinner() {
    lc.setRow(DISPLAY_ADDRESS, DISPLAY_DIGIT_0,B00000000);
    display_spinner_current = 0;
}