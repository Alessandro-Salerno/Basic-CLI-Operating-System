/*
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <https://unlicense.org>
*/

#include "shell.h"
#include "print.h"
#include "keyboard.h"
#include "ostime.h"
#include "ostypes.h"

#define SHELL_FOREGROUND PRINT_COLOR_WHITE
#define SHELL_BACKGROUND PRINT_COLOR_BLACK
#define SHELL_CURSOR_CHAR ' '
#define SHELL_CURSOR_COLOR SHELL_FOREGROUND, SHELL_FOREGROUND

static void shell_error(const char *errortext)
{
    print_set_color(PRINT_COLOR_RED, SHELL_BACKGROUND);
    print_str("\n");
    print_str("SHELL ERROR: ");
    print_str(errortext);
}

static void shell_display_cursor(uint8_t _col, uint8_t _row)
{
    print_set_color(SHELL_CURSOR_COLOR);
    print_char(SHELL_CURSOR_CHAR);
    print_moveto(_col, _row);
    print_set_color(SHELL_FOREGROUND, SHELL_BACKGROUND);
}

static void shell_dispatch_cursor(uint8_t _col, uint8_t _row)
{
    struct SCHAR _character = print_get_char_at(_col, _row);

    if (_character.character == ' ')
    {
        print_moveto(_col, _row);
        print_set_color(SHELL_FOREGROUND, SHELL_BACKGROUND);
        print_str(" ");
    }
}

static int8_t shell_draw_cursor()
{
    static uint8_t prevx, prevy;
    static uint8_t _col, _row;

    if (2 != print_get_console_handles(NULL, &_col, &_row))
    {
        shell_error("Output Manager returned invalid handler\n");
        return -1;
    }

    shell_dispatch_cursor(prevx, _row - 1);
    print_moveto(_col, _row);
    shell_display_cursor(_col, _row);

    prevx = _col;
    prevy = _row;
}

static void shell_backspace()
{
    uint8_t _col, _row;

    print_get_console_handles(NULL, &_col, &_row);
    print_moveto(_col - 1, _row);
    print_str("  ");
    print_moveto(_col - 1, _row);
}

static uint8_t shell_handle_input(uint8_t *_retchar)
{
    char _char = 0;
    char _keycode = 0;

    static uint8_t _shift = FALSE;
    uint8_t _col, _row;

    if (!((_keycode = keyboard_read()) > 0))
        return 0;

    switch (_keycode)
    {
    case KEY_ENTER:
        break;
    case KEY_BACKSPACE:
        break;

    case KEY_SHIFT:
        _shift = TRUE;
        break;

    default:
        _char = char_scancode_to_ascii(_keycode);
        print_char(_char = char_shift(_char, _shift));
        if (_retchar != NULL)
            (*_retchar) = _char;
        _shift = FALSE;
        break;
    }

    shell_draw_cursor();
    while (_keycode == keyboard_read())
        continue;

    return _keycode;
}

void shell_input(char *_buff, uint16_t _buffsize)
{
    char _keycode = 0,
         _char = 0;

    uint16_t _index = 0;

    while (((_keycode = shell_handle_input(&_char)) != KEY_ENTER) && _index < _buffsize)
    {
        shell_draw_cursor();

        switch (_keycode)
        {
        case 0:
            break;

        case KEY_BACKSPACE:
            if (_index > 0)
            {
                _buff[_index] = '\0';
                _index--;

                shell_backspace();
            }
            break;

        default:
            _buff[_index] = _char;
            _index++;
            break;
        }
    }

    print_char('\n');
    shell_draw_cursor();
}

void shell_main()
{
    char _inputbuffer[256];

    while (TRUE)
    {
        print_set_color(SHELL_FOREGROUND, SHELL_BACKGROUND);
        print_str("\n$ ");

        for (int i = 0; i < 256; i++)
            _inputbuffer[i] = '\0';

        shell_input(_inputbuffer, 256);
        print_str(_inputbuffer);
        print_str("\n");
    }
}
