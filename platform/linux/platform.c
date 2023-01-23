#include "platform.h"

#include "core/error_list.h"
#include "include/display_x11.h"
#include "include/gl_context.h"
#include <stdlib.h>
#include "core/logger.h"
#include "input.h"

#include <string.h>
#include <stdio.h>

void print_hello()
{
    printf("Hello, World!\n");
}

b8 platform_init(PlatformDisplay *platform_display, const char *window_title,
                uint32 x, uint32 y, uint32 width, uint32 height)
{
     PlatformDisplay *dp = (PlatformDisplay *) platform_display;
    dp->_window = malloc(sizeof(DisplayX11));
    dp->_context = malloc(sizeof(GLContext));

    // Create LFWindow
    int rvalue = displayx11_setup(dp->_window);
    if(rvalue != OK)
    {
        LF_FATAL(ERR_WINDOW, "displayx11_setup rvalue = %d", rvalue);
        return rvalue;
    }

    // Create OpenGL context
	rvalue = glcontext_create(dp->_context, dp->_window);
	if(rvalue != OK)
    {
        LF_FATAL(ERR_CONTEXT, "context_create rvalue = %d", rvalue);
        return rvalue;
    }
    
    rvalue = displayx11_create(dp->_window, window_title, x, y, width, height);
	if(rvalue != OK)
    {
        LF_FATAL(ERR_WINDOW, "x11window_create rvalue = %d", rvalue);
        return rvalue;
    }

    // Make OpenGL context current
    rvalue = glcontext_make_current(dp->_context, dp->_window);
	if(rvalue != OK)
    {
        LF_FATAL(ERR_CONTEXT, "context_make_current rvalue = %d", rvalue);
        return rvalue;
    }

    // Disable key repeat(update stutters it we don't disable)
    DisplayX11 *w = (DisplayX11 *) dp->_window;
    XAutoRepeatOff(w->display);
    
    // Initialize input system
    input_init();
    LF_DEBUG("Input is initialized.");

    // Set platform_display to be running
    dp->_running = TRUE;

    // Show window
    displayx11_show(w);

    return OK;
}

b8 is_platform_running(PlatformDisplay *platform_display)
{
    PlatformDisplay *dp = (PlatformDisplay *) platform_display;
    return dp->_running;
}

void set_platform_running(PlatformDisplay *platform_display, b8 value)
{
    PlatformDisplay *dp = (PlatformDisplay *) platform_display;
    dp->_running = value;
}

void platform_process_events(PlatformDisplay *platform_display)
{
    PlatformDisplay *dp = (PlatformDisplay *) platform_display;
    DisplayX11 *w = (DisplayX11 *) dp->_window;
    GLContext *glc = (GLContext *) dp->_context;

    XEvent ev;
    char str[25];
    KeySym keysym;
    Keys key;

    if(XPending(w->display) > 0)
    {
        XNextEvent(w->display, &ev);

        switch(ev.type)
        {
            case ButtonRelease:
            case ButtonPress: {
                b8 button_pressed = ev.type == ButtonPress;
                Buttons mouse_button = MAX_BUTTONS;
                switch(ev.xbutton.button){
                    case 1:
                        mouse_button = BUTTON_LEFT;
                        break;
                    case 2:
                        mouse_button = BUTTON_MIDDLE;
                        break;
                    case 3:
                        mouse_button = BUTTON_RIGHT;
                        break;
                }
                
                if(mouse_button != MAX_BUTTONS){
                    input_process_button(mouse_button, button_pressed);
                    input_update();
                }
            } break;

            case KeyRelease:
            case KeyPress:{
                int len = XLookupString(&ev.xkey, str, 25, &keysym, NULL);
                if(len > 0){
                    b8 pressed = ev.type == KeyPress;
                    key = translate_keycode(keysym);
                    input_process_key(key, pressed);
                    input_update();
                }
            } break;
            case LeaveNotify:
            case EnterNotify:
                break;
            case MotionNotify:
                break;
            case ConfigureNotify:
                break;
            case ClientMessage:{
                if (ev.xclient.data.l[0] == w->delete_msg) {
                    dp->_running = FALSE;
                }
            } break;
            case DestroyNotify:
                break;
        }
    }

    XFlush(w->display);
}

void platform_shutdown(PlatformDisplay *platform_display)
{
    PlatformDisplay *dp = (PlatformDisplay *) platform_display;
    DisplayX11 *w = (DisplayX11 *) dp->_window;

    // Enable key repeat
    XAutoRepeatOn(w->display);
    LF_DEBUG("AutoRepeatON!");

    // Cleanup GLX
	glcontext_destroy(dp->_context, dp->_window);

	// Cleanup X11
	displayx11_destroy(dp->_window, dp->_context);
}

void platform_swap_buffers(PlatformDisplay *platform_display)
{
    PlatformDisplay *dp = (PlatformDisplay *) platform_display;
    DisplayX11 *w = (DisplayX11 *) dp->_window;
    GLContext *glc = (GLContext *) dp->_context;

    glXSwapBuffers(w->display, w->id);
}

void* platform_zero_memory(void *block, ullong64 size)
{
    return memset(block, 0, size);
}

void* platform_copy_memory(void *destiny, const void *source, ullong64 size)
{
    return memcpy(destiny, source, size);
}

void* platform_set_memory(void *destiny, sint32 value, ullong64 size)
{
    return memset(destiny, value, size);
}