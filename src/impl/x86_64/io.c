#include "io.h"


uint8_t port_in_byte(uint16_t address) {
    uint8_t ret;
    asm volatile("inb %1, %0" : "=a"(ret) : "d"(address));
    return ret;
}

void port_out_byte(uint16_t address, uint8_t byte) {
    asm volatile("outb %0, %1" : "=a"(byte) : "d"(address));
}
