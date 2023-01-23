#ifndef MEMORY_H
#define MEMORY_H

#include "defines.h"

// Set memory to 0
void* zero_memory(void *block, ullong64 size);

// Copy memory from source to destiny
void* copy_memory(void *destiny, const void* source, ullong64 size);

// Set memory to value
void* set_memory(void *destiny, sint32 value, ullong64 size);

#endif // MEMORY_H