#include <stdint.h>
#include <stdlib.h>

uint32_t allocator_calcualteByteCount(uint32_t amount, uint32_t itemByteSize);
void* allocator_allocate(uint32_t amount, uint32_t itemByteSize);
void* allocator_allocateDefaultUint32_t(uint32_t amount, uint32_t defaultValue);
void* allocator_allocateDefault(uint32_t amount, uint32_t itemByteSize,void* defaultValue);
void* allocator_free(void* dataPtr, uint32_t amount, uint32_t itemByteSize);
