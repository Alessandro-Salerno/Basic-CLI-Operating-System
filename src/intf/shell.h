#pragma once

#include <stdint.h>


static void shell_error(const char* errortext);
static void shell_display_cursor(uint8_t _col, uint8_t _row);
static void shell_dispatch_cursor(uint8_t _col, uint8_t _row);
static int8_t draw_cursor();
void shell_main();
