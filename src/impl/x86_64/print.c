#include "print.h"


static const size_t NUM_COLS  = 80;
static const size_t NUM_ROWS  = 25;
static const size_t START_COL = 0;
static const size_t START_ROW = NUM_ROWS - 1;

       struct SCHAR*   buffer = (struct SCHAR*)(0xB8000);
static        uint8_t  col    = START_COL;
static        uint8_t  row    = START_ROW;
static        uint8_t  color  = PRINT_COLOR_WHITE | PRINT_COLOR_BLACK << 4;


static void clear_row(uint8_t row) {
    struct SCHAR empty = (struct SCHAR) {
        character: ' ',
        color: color,
    };

    for (uint8_t c = 0; c < NUM_COLS; c++)
        buffer[c + NUM_COLS * row] = empty;
}

void print_clear() {
    for (uint8_t i = 0; i < NUM_ROWS; i++)
        clear_row(i);

    col = START_COL;
    row = START_ROW;
}

void print_newline() {
    col = 0;

    if (row < NUM_ROWS - 1) {
        row++;
        return;
    }

    for (uint8_t r = 1; r < NUM_ROWS; r++) {
        for (uint8_t c = 0; c < NUM_COLS; c++) {
            struct SCHAR character = buffer[c + NUM_COLS * r];
            buffer[c + NUM_COLS * (r - 1)] = character;
        }
    }

    clear_row(NUM_ROWS - 1);
}

void print_char(char character) {
    if (character == '\0' || character == NULL || character == 0)
        return;
    
    if (character == '\n') {
        print_newline();
        return;
    }

    if (col > NUM_COLS)
        print_newline();

    buffer[col + NUM_COLS * row] = (struct SCHAR) {
        character: (uint8_t)(character),
        color: color,
    };

    col++;
}

void print_str(const char* str) {
    char character;
    for (uint64_t i = 0; (character = (uint8_t)(str[i])) != '\0'; i++)
        print_char(character);
}

void print_set_color(uint8_t foreground, uint8_t background) {
    color = foreground + (background << 4);
}

void print_moveto(uint8_t x, uint8_t y) {
    col = x;
    row = y;
}

uint8_t print_get_console_handles(struct SCHAR** buff, uint8_t* c, uint8_t* r) {
    uint8_t count = 0;
    
    (count += buff != NULL) ? (*buff) = buffer : NULL;
    (count += c    != NULL) ? (*c)    = col    : NULL;
    (count += r    != NULL) ? (*r)    = row    : NULL;

    return count;
}

uint8_t print_get_console_constants(uint8_t* num_cols, uint8_t* num_rows, uint8_t* start_column, uint8_t* start_row) {
    uint8_t count = 0;
    
    (count += num_cols     != NULL) ? (*num_cols)     = NUM_COLS  : NULL;
    (count += num_rows     != NULL) ? (*num_rows)     = NUM_ROWS  : NULL;
    (count += start_column != NULL) ? (*start_column) = START_COL : NULL;
    (count += start_row    != NULL) ? (*start_row)    = START_ROW : NULL;

    return count;
}
