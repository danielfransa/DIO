#include "input.h"

#include <stdio.h>
#include <termios.h>
#include <unistd.h>

static struct termios original_termios;
static int raw_mode_enabled = 0;

int input_enable_raw_mode(void)
{
    struct termios raw;

    if (tcgetattr(STDIN_FILENO, &original_termios) == -1) {
        return 0;
    }

    raw = original_termios;
    raw.c_lflag &= (tcflag_t) ~(ECHO | ICANON | ISIG);
    raw.c_cc[VMIN] = 1;
    raw.c_cc[VTIME] = 0;

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) {
        return 0;
    }

    raw_mode_enabled = 1;
    return 1;
}

void input_disable_raw_mode(void)
{
    if (raw_mode_enabled) {
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_termios);
        raw_mode_enabled = 0;
    }
}

Key input_read_key(void)
{
    int ch = getchar();

    if (ch == EOF) {
        return KEY_NONE;
    }

    if (ch == 3) {
        return KEY_CTRL_C;
    }

    if (ch == ' ') {
        return KEY_SPACE;
    }

    if (ch == '\r' || ch == '\n') {
        return KEY_ENTER;
    }

    if (ch == '\033') {
        int next = getchar();
        int code = getchar();

        if (next != '[') {
            return KEY_NONE;
        }

        switch (code) {
            case 'A':
                return KEY_UP;
            case 'B':
                return KEY_DOWN;
            case 'C':
                return KEY_RIGHT;
            case 'D':
                return KEY_LEFT;
            default:
                return KEY_NONE;
        }
    }

    return KEY_NONE;
}
