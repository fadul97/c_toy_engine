#include "memory.h"

#include "platform.h"

void* zero_memory(void *block, ullong64 size)
{
    return platform_zero_memory(block, size);
}

void* copy_memory(void *destiny, const void* source, ullong64 size)
{
    return platform_copy_memory(destiny, source, size);
}

void* set_memory(void *destiny, sint32 value, ullong64 size)
{
    return platform_set_memory(destiny, value, size);
}
