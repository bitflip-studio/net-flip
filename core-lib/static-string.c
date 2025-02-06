#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "./allocator.c"


uint8_t* staticString_create(uint32_t size, const uint8_t* encoded_path) {
    uint8_t* str = (uint8_t*) allocator_allocate(1, sizeof(uint32_t) + size);
    if(NULL != str) {
        if(str != memcpy(str, &size, sizeof(uint32_t))) {
            str = allocator_free(str, 1, sizeof(uint32_t) + size);
            return NULL;
        }
        if((str + sizeof(uint32_t)) != memcpy(str + sizeof(uint32_t), encoded_path, size)) {
            str = allocator_free(str, 1, sizeof(uint32_t) + size);
            return NULL;
        }
    }
    return str;
}