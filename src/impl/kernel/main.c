#include "print.h"
#include "ostypes.h"
#include "shell.h"
#include "keyboard.h"
#include "ostime.h"


void kernel_main() {
    print_clear();
    print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
    
    print_str("WARN: This software is in Alpha and comes with no warranty or support.\n\n");
    print_set_color(PRINT_COLOR_BLUE, PRINT_COLOR_BLACK);
    
    print_str("Copyright Alessandro Salerno 2021. All Rights Reserved.\n");
    print_str("SalernOS Kernel v0.0.3!\n\n");

    shell_main();
}
