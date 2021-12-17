#pragma once

#include <stdint.h>
#include <stddef.h>
#include "ostypes.h"


enum {
    PRINT_COLOR_BLACK       = 0,
	PRINT_COLOR_BLUE        = 1,
	PRINT_COLOR_GREEN       = 2,
	PRINT_COLOR_CYAN        = 3,
	PRINT_COLOR_RED         = 4,
	PRINT_COLOR_MAGENTA     = 5,
	PRINT_COLOR_BROWN       = 6,
	PRINT_COLOR_LIGHT_GRAY  = 7,
	PRINT_COLOR_DARK_GRAY   = 8,
	PRINT_COLOR_LIGHT_BLUE  = 9,
	PRINT_COLOR_LIGHT_GREEN = 10,
	PRINT_COLOR_LIGHT_CYAN  = 11,
	PRINT_COLOR_LIGHT_RED   = 12,
	PRINT_COLOR_PINK        = 13,
	PRINT_COLOR_YELLOW      = 14,
	PRINT_COLOR_WHITE       = 15,
};

void print_clear();
void print_char(char character);
void print_str(const char* string);
void print_set_color(uint8_t foreground, uint8_t background);
void print_moveto(uint8_t x, uint8_t y);
uint8_t print_get_console_handles(struct SCHAR** buff, uint8_t* c, uint8_t* r);
uint8_t print_get_console_constants(uint8_t* num_cols, uint8_t* num_rows, uint8_t* start_column, uint8_t* start_row);
