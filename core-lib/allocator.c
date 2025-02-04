#include "./allocator.h"
#include <string.h>

uint64_t usedMemotyBytes = 0;


uint32_t allocator_calcualteByteCount(uint32_t amount, uint32_t itemByteSize) {
    return amount * itemByteSize;
}

void* allocator_allocate(uint32_t amount, uint32_t itemByteSize) {
  uint32_t dataByteSize = allocator_calcualteByteCount(amount, itemByteSize);
  void* dataPtr = malloc(dataByteSize);
  if(NULL != dataPtr) {
    usedMemotyBytes += dataByteSize;
  }
  return dataPtr;
}

void* allocator_allocateDefaultUint32_t(uint32_t amount, uint32_t defaultValue) {
  void* dataPtr = allocator_allocate(amount, sizeof(uint32_t));
  for(uint32_t i = 0; i < amount; i++) {
    *(uint32_t*)(dataPtr + i * sizeof(uint32_t)) = defaultValue;
  }
  return dataPtr;
}

void* allocator_allocateDefault(uint32_t amount, uint32_t itemByteSize,void* defaultValue) {
  void* dataPtr = allocator_allocate(amount, itemByteSize);
  for(uint32_t i = 0; i < amount; i++) {
    if(memcpy(dataPtr + i * itemByteSize, defaultValue, itemByteSize) != dataPtr + i * itemByteSize) {
      free(dataPtr);
      dataPtr = NULL;
      break;
    }
  }
  return dataPtr;
}

void* allocator_free(void* dataPtr, uint32_t amount, uint32_t itemByteSize) {
  if(NULL != dataPtr) {
    free(dataPtr);
  	usedMemotyBytes -= allocator_calcualteByteCount(amount, itemByteSize);
  }
  return NULL;
}
