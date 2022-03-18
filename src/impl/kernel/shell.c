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
#include "easy.h"

#define SHELL_FOREGROUND PRINT_COLOR_WHITE
#define SHELL_BACKGROUND PRINT_COLOR_BLACK
#define SHELL_CURSOR_CHAR ' '
#define SHELL_CURSOR_COLOR SHELL_FOREGROUND, SHELL_FOREGROUND

static void shell_error(const char *errortext)
{
    textcolor(PRINT_COLOR_RED, SHELL_BACKGROUND);
    printf("\n");
    printf("SHELL ERROR: ");
    printf(errortext);
}

static void shell_display_cursor(int col, int row)
{
    textcolor(SHELL_CURSOR_COLOR);
    print_char(SHELL_CURSOR_CHAR);
    gotoxy(col, row);
    textcolor(SHELL_FOREGROUND, SHELL_BACKGROUND);
}

static void shell_dispatch_cursor(int col, int row)
{
    struct BIOSChar _character = print_get_char_at(col, row);

    if (_character.character == ' ')
    {
        gotoxy(col, row);
        textcolor(SHELL_FOREGROUND, SHELL_BACKGROUND);
        printf(" ");
    }
}

static int shell_draw_cursor()
{
    static int prevx, prevy;
    static int col, row;

    if (2 != print_get_console_handles(NULL, &col, &row))
    {
        shell_error("Output Manager returned invalid handler\n");
        return -1;
    }

    shell_dispatch_cursor(prevx, row - 1);
    gotoxy(col, row);
    shell_display_cursor(col, row);

    prevx = col;
    prevy = row;
}

static void shell_backspace()
{
    int col, row;

    print_get_console_handles(NULL, &col, &row);
    gotoxy(col - 1, row);
    printf("  ");
    gotoxy(col - 1, row);
}

static int shell_handle_input(uint8_t *retchr)
{
    char chr = 0;
    char kcode = 0;

    static uint8_t shiftPressed = false;
    int col, row;

    if (!((kcode = keyboard_read()) > 0))
        return 0;

    switch (kcode)
    {
    case KEY_ENTER:
        break;
    case KEY_BACKSPACE:
        break;

    case KEY_SHIFT:
        shiftPressed = true;
        break;

    default:
        chr = char_scancode_to_ascii(kcode);
        print_char(chr = char_shift(chr, shiftPressed));
        if (retchr != NULL)
            (*retchr) = chr;
        shiftPressed = false;
        break;
    }

    shell_draw_cursor();
    while (kcode == keyboard_read())
        continue;

    return kcode;
}

void shell_input(char *buffer, int buffersize)
{
    char kcode = 0,
         chr = 0;

    int index = 0;

    while (((kcode = shell_handle_input(&chr)) != KEY_ENTER) && index < buffersize)
    {
        shell_draw_cursor();

        switch (kcode)
        {
        case 0:
            break;

        case KEY_BACKSPACE:
            if (index > 0)
            {
                buffer[index] = '\0';
                index--;

                shell_backspace();
            }
            break;

        default:
            buffer[index] = chr;
            index++;
            break;
        }
    }

    print_char('\n');
    shell_draw_cursor();
}

void shell_main()
{
    char inputBuffer[256];

    while (true)
    {
        textcolor(SHELL_FOREGROUND, SHELL_BACKGROUND);
        printf("\n$ ");

        for (int i = 0; i < 256; i++)
            inputBuffer[i] = '\0';

        scanf(inputBuffer, 256);
        printf(inputBuffer);
        printf("\n");
    }
}
