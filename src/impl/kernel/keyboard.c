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


#include "keyboard.h"
#include "io.h"


char char_scancode_to_ascii(uint8_t _keycode) {
    switch (_keycode) {
        // Letters
        case KEY_A                    : return 'a';
        case KEY_B                    : return 'b';
        case KEY_C                    : return 'c';
        case KEY_D                    : return 'd';
        case KEY_E                    : return 'e';
        case KEY_F                    : return 'f';
        case KEY_G                    : return 'g';
        case KEY_H                    : return 'h';
        case KEY_I                    : return 'i';
        case KEY_J                    : return 'j';
        case KEY_K                    : return 'k';
        case KEY_L                    : return 'l';
        case KEY_M                    : return 'm';
        case KEY_N                    : return 'n';
        case KEY_O                    : return 'o';
        case KEY_P                    : return 'p';
        case KEY_Q                    : return 'q';
        case KEY_R                    : return 'r';
        case KEY_S                    : return 's';
        case KEY_T                    : return 't';
        case KEY_U                    : return 'u';
        case KEY_V                    : return 'v';
        case KEY_W                    : return 'w';
        case KEY_X                    : return 'x';
        case KEY_Y                    : return 'y';
        case KEY_Z                    : return 'z';

        // Numbers
        case KEY_1                    : return '1';
        case KEY_2                    : return '2';
        case KEY_3                    : return '3';
        case KEY_4                    : return '4';
        case KEY_5                    : return '5';
        case KEY_6                    : return '6';
        case KEY_7                    : return '7';
        case KEY_8                    : return '8';
        case KEY_9                    : return '9';
        case KEY_0                    : return '0';

        // Symbols
        case KEY_MINUS                : return '-';
        case KEY_EQUAL                : return '=';
        case KEY_SQUARE_OPEN_BRACKET  : return '[';
        case KEY_SQUARE_CLOSE_BRACKET : return ']';
        case KEY_SEMICOLON            : return ';';
        case KEY_BACKSLASH            : return '\\';
        case KEY_COMMA                : return ',';
        case KEY_DOT                  : return '.';
        case KEY_FORESLHASH           : return '/';

        // Misc
        case KEY_SPACE                : return ' ';
    }
}

char char_shift(char chr, uint8_t _shift) {
    return (_shift) ? chr & ~(1 << 5) : chr | (1 << 5);
}

char keyboard_read() {
    return port_in_byte(KEYBOARD_PORT);
}
