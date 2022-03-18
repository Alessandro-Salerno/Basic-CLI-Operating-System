#include "easy.h"


void printf(const char* text)
{
    print_str(text);
}

void scanf(char* buffer, int buffersize)
{
    shell_input(buffer, buffersize);
}

void gotoxy(int x, int y)
{
    print_moveto(x, y);
}

void textcolor(int foreground, int background)
{
    print_set_color(foreground, background);
}
