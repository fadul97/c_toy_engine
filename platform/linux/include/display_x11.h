#ifndef DISPLAY_X11_H
#define DISPLAY_X11_H

#include "core/defines.h"

#include <X11/Xlib.h>
#include <X11/Xutil.h>

typedef struct DisplayX11{
    Display *display;
    ulong32 id;
    Screen *screen;
    sint32 screen_id;
    XSetWindowAttributes x_window_attribs;
    XVisualInfo *visual;
    ulong32 delete_msg;
} DisplayX11;

struct GLContext;

sshort16 displayx11_setup(DisplayX11 *display_x11);
sshort16 displayx11_create(DisplayX11 *display_x11, const char *title,
                    uint32 x, uint32 y, uint32 width, uint32 height);

void displayx11_show(DisplayX11 *display_x11);
void displayx11_destroy(DisplayX11 *display_x11, struct GLContext *gl_context);

#endif // DISPLAY_X11_H