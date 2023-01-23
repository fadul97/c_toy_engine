#include <stdio.h>

#include "engine.h"
#include <glad/gl.h>

int main(int argc, char **argv)
{
    int r = toyengine_init();
    if(r != 0)
    {
        printf("r = %d\n", r);
        return r;
    }

    while(toyengine_loop())
    {
        if(is_key_down(KEY_ESCAPE))
            toyengine_close_window();

        glClearColor(0.6f, 0.6f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        toyengine_swap_buffers();
        toyengine_process_events();
    }

    toyengine_shutdown();
    return 0;
}