#include <stdio.h>
#include "libcore.h"
#include <stdint.h>


uint32_t encodeVersion(uint8_t major, uint8_t minor, uint16_t patch);

void say_hello() {
    printf("Hello from libcore!\n");
}

uint32_t VERSION() {
    return encodeVersion(0,0,2);
}

uint32_t encodeVersion(uint8_t major, uint8_t minor, uint16_t patch) {
    return ((uint32_t)major << 24) | ((uint32_t)minor << 16) | (uint32_t)patch;
}