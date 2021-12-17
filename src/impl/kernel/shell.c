#include "shell.h"
#include "print.h"
#include "keyboard.h"
#include "ostime.h"


#define SHELL_FOREGROUND  PRINT_COLOR_WHITE
#define SHELL_BACKGROUND  PRINT_COLOR_BLACK
#define SHELL_CURSOR_CHAR ' '
#define SHELL_CURSOR_COLOR SHELL_FOREGROUND, SHELL_FOREGROUND


static void shell_error(const char* errortext) {
    print_set_color(PRINT_COLOR_RED, SHELL_BACKGROUND);
    print_str("\n");
    print_str(errortext);
}

static void shell_display_cursor(uint8_t _col, uint8_t _row) {
    print_set_color(SHELL_CURSOR_COLOR);
    print_char(SHELL_CURSOR_CHAR);
    print_moveto(_col, _row);
    print_set_color(SHELL_FOREGROUND, SHELL_BACKGROUND);
}

static void shell_dispatch_cursor(uint8_t _col, uint8_t _row) {
    print_moveto(_col, _row);
    print_set_color(SHELL_BACKGROUND, SHELL_BACKGROUND);
    print_str(" ");
}

static int8_t shell_draw_cursor() {
    static uint8_t prevx, prevy;
    static uint8_t _col, _row;

    prevx = _col;
    prevy = _row;

    if (2 != print_get_console_handles(NULL, &_col, &_row)) {
        shell_error("SHELL ERROR: Output Manager returned invalid handler\n");
        return -1;
    }

    if (prevy != _row) {
        shell_dispatch_cursor(prevx, prevy);
        print_moveto(_col, _row);
    }

    shell_display_cursor(_col, _row);
}

static uint8_t shell_handle_input() {
    char chr = 0;
    char keycode = 0;
    uint8_t _col, _row;

    while ((keycode = keyboard_read()) > 0) {
        switch (keycode)
        {
            case KEY_ENTER:
                print_str("\n");
                break;

            case KEY_BACKSPACE:
                print_get_console_handles(NULL, &_col, &_row);

                if (_col == 0)
                    break;
                
                print_moveto(_col - 1, _row);
                print_str("  ");
                print_moveto(_col - 1, _row);
                break;
            
            default:
                chr = char_scancode_to_ascii(keycode);
                print_char(chr);
                break;
        }

        while (keycode == keyboard_read()) {
            continue;
        }

        return keycode;
    }
}

void shell_main() {
    while (TRUE) {
        print_set_color(SHELL_FOREGROUND, SHELL_BACKGROUND);
        print_str("\n$ ");

        while (shell_handle_input() != KEY_ENTER)
            if (-1 == shell_draw_cursor())
                return;
    }
}
