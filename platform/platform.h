#ifndef PLATFORM_H
#define PLATFORM_H

#include "core/defines.h"

typedef struct PlatformDisplay
{
    void* _window;
    void* _context;
    b8 _running;
} PlatformDisplay;

void print_hello();

// Setup platform_display
b8 platform_init(PlatformDisplay *platform_display, const char *window_title,
                uint32 x, uint32 y, uint32 width, uint32 height);

// Handle platform loop
b8 is_platform_running(PlatformDisplay *platform_display);
void set_platform_running(PlatformDisplay *platform_display, b8 value);

// Handle platform events (key/button/graphics input...)
void platform_process_events(PlatformDisplay *platform_display);

// Cleanup
void platform_shutdown(PlatformDisplay *platform_display);

// Swap buffers
void platform_swap_buffers(PlatformDisplay *platform_display);

// Set block memory to 0
void* platform_zero_memory(void *block, ullong64 size);

// Copy memory from source to destiny
void* platform_copy_memory(void *destiny, const void *source, ullong64 size);

// Set destiny memory to value
void* platform_set_memory(void *destiny, sint32 value, ullong64 size);

#endif // PLATFORM_H