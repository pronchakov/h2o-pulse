#ifndef pulse_logic_h_
#define pulse_logic_h_

    #define PULSE_PARAM_TYPE_TIME 1
    #define PULSE_PARAM_TYPE_VOLUME 2

    enum ParamType {Time, Volume};

    void logic_tick();
    void logic_setup();
    ParamType logic_get_current_param();
    void logic_change_type();
    void logic_set_value(int value);
    void logic_increment_value();
    void logic_decrement_value();
    void logic_button_pushed();

#endif