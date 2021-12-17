#pragma once

#include <stdint.h>
#include <stddef.h>


uint8_t port_in_byte(uint16_t address);
void port_out_byte(uint16_t address, uint8_t byte);
