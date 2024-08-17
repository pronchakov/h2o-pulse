#ifndef pulse_display_h_
#define pulse_display_h_

    #include <pulse_logic.h>

    void display_setup();
    void display_show_value(ParamType type, int value);
    void display_show_type(ParamType type);
    void display_move_spinner();
    void display_clear_spinner();

#endif