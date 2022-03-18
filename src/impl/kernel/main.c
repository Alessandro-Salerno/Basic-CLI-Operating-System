#include "print.h"
#include "ostypes.h"
#include "shell.h"
#include "keyboard.h"
#include "ostime.h"


void kernel_main() {
    print_clear();
    print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
    
    print_str("WARN: This software comes with no warranty or support.\n\n");
    print_set_color(PRINT_COLOR_BLUE, PRINT_COLOR_BLACK);
    
    print_str("This software is in the Public Domain and is distributed under the \"Unlicese\".\n");
    print_str("Basic Kernel v0.0.4!\n\n");

    shell_main();
}
