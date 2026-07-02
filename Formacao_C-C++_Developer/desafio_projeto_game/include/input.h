#ifndef INPUT_H
#define INPUT_H

typedef enum {
    KEY_NONE,
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_SPACE,
    KEY_ENTER,
    KEY_CTRL_C
} Key;

int input_enable_raw_mode(void);
void input_disable_raw_mode(void);
Key input_read_key(void);

#endif
