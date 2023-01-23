#include "engine.h"

#include "platform/platform.h"

PlatformDisplay pd = {};

b8 toyengine_init()
{
    return platform_init(&pd, "ToyEngine", 100, 100, 800, 600);
}

b8 toyengine_loop()
{
    return is_platform_running(&pd);
}

void toyengine_process_events()
{
    platform_process_events(&pd);
}

void toyengine_swap_buffers()
{
    platform_swap_buffers(&pd);
}

void toyengine_close_window()
{
    set_platform_running(&pd, FALSE);
}


void toyengine_shutdown()
{
    platform_shutdown(&pd);
}