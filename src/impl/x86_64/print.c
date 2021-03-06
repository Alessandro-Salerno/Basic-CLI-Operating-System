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

#include "print.h"

static const int NUM_COLS = 80;
static const int NUM_ROWS = 25;
static const int START_COL = 0;
static const int START_ROW = NUM_ROWS - 1;

struct BIOSChar *buffer = (struct BIOSChar *)(0xB8000);
static int col = START_COL;
static int row = START_ROW;
static int color = PRINT_COLOR_WHITE | PRINT_COLOR_BLACK << 4;

static void clear_row(int row)
{
    struct BIOSChar empty = (struct BIOSChar){
        character : ' ',
        color : color,
    };

    for (int c = 0; c < NUM_COLS; c++)
        buffer[c + NUM_COLS * row] = empty;
}

void print_clear()
{
    for (int i = 0; i < NUM_ROWS; i++)
        clear_row(i);

    col = START_COL;
    row = START_ROW;
}

void print_newline()
{
    col = 0;

    if (row < NUM_ROWS - 1)
    {
        row++;
        return;
    }

    for (int r = 1; r < NUM_ROWS; r++)
    {
        for (int c = 0; c < NUM_COLS; c++)
        {
            struct BIOSChar character = buffer[c + NUM_COLS * r];
            buffer[c + NUM_COLS * (r - 1)] = character;
        }
    }

    clear_row(NUM_ROWS - 1);
}

void print_char(char character)
{
    if (character == '\0')
        return;

    if (character == '\n')
    {
        print_newline();
        return;
    }

    if (col > NUM_COLS)
        print_newline();

    buffer[col + NUM_COLS * row] = (struct BIOSChar){
        character : (int)(character),
        color : color,
    };

    col++;
}

void print_str(const char *str)
{
    char character;
    for (uint64_t i = 0; (character = (int)(str[i])) != '\0'; i++)
        print_char(character);
}

void print_set_color(int foreground, int background)
{
    color = foreground + (background << 4);
}

void print_moveto(int x, int y)
{
    col = x;
    row = y;
}

int print_get_console_handles(struct BIOSChar **buff, int *c, int *r)
{
    int count = 0;

    if (count += buff != NULL)
        (*buff) = buffer;
    if (count += c != NULL)
        (*c) = col;
    if (count += r != NULL)
        (*r) = row;

    return count;
}

int print_get_console_constants(int *num_cols, int *num_rows, int *start_column, int *start_row)
{
    int count = 0;

    if (count += num_cols != NULL)
        (*num_cols) = NUM_COLS;
    if (count += num_rows != NULL)
        (*num_rows) = NUM_ROWS;
    if (count += start_column != NULL)
        (*start_column) = START_COL;
    if (count += start_row != NULL)
        (*start_row) = START_ROW;

    return count;
}

struct BIOSChar print_get_char_at(int col, int _row)
{
    return buffer[col + NUM_COLS * row];
}
