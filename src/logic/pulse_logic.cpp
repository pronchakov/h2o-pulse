#include <pulse_logic.h>

#include <pulse_valve.h>
#include <pulse_display.h>

#include <arduino-timer.h>
auto timer = timer_create_default();

class Type
{
    protected:
        int value;
        int backup_value;
    public:
        Type(int value) {
            this->value = value;
            this->backup_value = value;
        };
        void set_value(int value) {
            this->value = value;
        };
        void set_backup_value(int value) {
            this->backup_value = value; // TODO: use constructor for this
        };
        int get_backup_value() {
            return this->backup_value;
        };
        int get_value() {
            return this->value;
        };
        virtual ParamType get_type();
        virtual void increment();
        virtual void decrement();
        virtual void decrement_by_second();
    
};

class TypeTime : public Type {
    protected:
        ParamType type = ParamType::Time;
    public:
        TypeTime(int value) : Type(value) {};
        ParamType get_type() {
            return Time;
        };
        void increment() {
            this->value += 5;
            if (this->value > 9999) {
                this->value = 9999;
            }
        };
        void decrement() {
            if (this->value > 0) {
                this->value -= 5;
            }
            if (this->value < 0) {
                this->value = 0;
            }
        };
        void decrement_by_second() {
            this->value--;
            if (this->value < 0) {
                this->value = 0;
            }
        };
};

class TypeVolume : public Type {
    private:
        void decrement_by_value(int value) {
            if (this->value > 0) {
                this->value -= value;
            }
            if (this->value < 0) {
                this->value = 0;
            }
        };
    protected:
        ParamType type = ParamType::Volume;
    public:
        TypeVolume(int value) : Type(value) {};
        ParamType get_type() {
            return Volume;
        };
        void increment() {
            this->value += 50;
            if (this->value > 9999) {
                this->value = 9999;
            }
        };
        void decrement() {
            this->decrement_by_value(50);
        };
        void decrement_by_second() {
            this->decrement_by_value(11);
        };
};

TypeTime time(60);
TypeVolume volume(1700);

Type* current = &volume;
bool is_valve_open = false;

void logic_tick() {
    timer.tick<void>();
}

void display() {
    display_show_value(current->get_type(), current->get_value());
    display_show_type(current->get_type());
}

void open() {
    is_valve_open = true;
    current->set_backup_value(current->get_value());
    valve_open();
}

void close() {
    valve_close();
    is_valve_open = false;

    current->set_value(current->get_backup_value());
    display();
    // display_clear_spinner();
}

void logic_change_type() {
    if (!is_valve_open) {
        if (current == &time) {
            current = &volume;
        } else if (current == &volume) {
            current = &time;
        }

        display();
    }
}

ParamType logic_get_current_param() {
    return current->get_type();
}

void logic_set_value(int value) {
    current->set_value(value);
}

void logic_increment_value() {
    current->increment();
    display_show_value(current->get_type(), current->get_value());
}

void logic_decrement_value() {
    current->decrement();
    display_show_value(current->get_type(), current->get_value());
}

bool call_every_second(void *useless_argument) {
    if (is_valve_open) {
        current->decrement_by_second();
        
        if (current->get_value() <= 0) {
            close();
            return;
        }

        display();
        // display_move_spinner();
    } else {
        // Just in safety precausions... 
        valve_close();
    }
    return true;
}

void logic_button_pushed() {
    switch (is_valve_open){
        case true: close(); break;
        case false: open(); break;
    }
}

void logic_setup() {
    display();
    timer.every(1000, call_every_second);
}