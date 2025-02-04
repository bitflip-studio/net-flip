#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "./allocator.h"

typedef struct {
    uint32_t size;
    uint32_t startDataIndex;
    uint32_t endDataIndex; // including this data block
} DynamicStream_t;

typedef struct {
    uint32_t 	     itemByteSize;
    uint32_t 		 bufferAmount;
    uint8_t* 		 data;
    uint32_t* 		 nextDataIndexTable;
    uint32_t         freeDataIndex;

    uint32_t 		 streamAmount;
	DynamicStream_t* streams;
    uint32_t* 		 nextStreamIndexTable;
    uint32_t         freeStreamIndex;
} DynamicStreamContext_t;

bool dynamicStream_init(DynamicStreamContext_t* context, uint32_t bufferAmount, uint32_t itemByteSize, uint32_t streamAmount);
DynamicStreamContext_t * dynamicStream_alloc();
void* dynamicStream_free(void* dynamicStream_ptr);
void dynamicStream_destroy(DynamicStreamContext_t* context);
void* dynamicStream_free(void* dynamicStream_ptr);

DynamicStreamContext_t * dynamicStream_alloc() {
     return (DynamicStreamContext_t*) allocator_allocate(1, sizeof(DynamicStreamContext_t));
}

bool dynamicStream_init(DynamicStreamContext_t* context, uint32_t bufferAmount, uint32_t itemByteSize, uint32_t streamAmount) {
    context->data = (uint8_t*) allocator_allocate(bufferAmount, itemByteSize);
    if(NULL == context->data) {
      return false;
    }

    context->nextDataIndexTable = (uint32_t*) allocator_allocateDefaultUint32_t(bufferAmount, -1);
    if(NULL == context->nextDataIndexTable) {
        context->data = allocator_free(context->data, bufferAmount, itemByteSize);
        return false;
    }

    context->streams = (DynamicStream_t*) allocator_allocate(streamAmount, sizeof(DynamicStream_t));
    if(NULL == context->streams) {
      context->nextDataIndexTable = allocator_free(context->nextDataIndexTable, bufferAmount, itemByteSize);
      context->data = allocator_free(context->data, bufferAmount, itemByteSize);
      return false;
    }

    context->nextStreamIndexTable = (uint32_t*) allocator_allocateDefaultUint32_t(streamAmount, -1);
    if(NULL == context->nextStreamIndexTable) {
      context->streams = allocator_free(context->streams, streamAmount, sizeof(DynamicStream_t));
      context->nextDataIndexTable = allocator_free(context->nextDataIndexTable, bufferAmount, sizeof(uint32_t));
      context->data = allocator_free(context->data, bufferAmount, itemByteSize);
      return false;
    }

    context->itemByteSize = itemByteSize;
    context->bufferAmount = bufferAmount;
    context->streamAmount = streamAmount;
    context->freeDataIndex = 0;
    context->freeStreamIndex = 0;

    return true;
}

//DynamicStream_t* dynamicStream_createStream(DynamicStreamContext_t* context) {
//
//}

void dynamicStream_destroy(DynamicStreamContext_t* context) {
  context->nextStreamIndexTable = allocator_free(context->nextStreamIndexTable, context->streamAmount, sizeof(uint32_t));
  context->streams = allocator_free(context->streams, context->streamAmount, sizeof(DynamicStream_t));
  context->nextDataIndexTable = allocator_free(context->nextDataIndexTable, context->bufferAmount, sizeof(uint32_t));
  context->data = allocator_free(context->data, context->bufferAmount, context->itemByteSize);
}

void* dynamicStream_free(void* dynamicStream_ptr) {
  return allocator_free(dynamicStream_ptr, 1, sizeof(DynamicStreamContext_t));
}