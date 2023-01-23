#ifndef TOY_ENGINE_H
#define TOY_ENGINE_H

#include "core/defines.h"
#include "platform/input.h"

b8 toyengine_init();
b8 toyengine_loop();
void toyengine_process_events();
void toyengine_close_window();
void toyengine_shutdown();

// Swap buffers
void toyengine_swap_buffers();

#endif // TOY_ENGINE_H