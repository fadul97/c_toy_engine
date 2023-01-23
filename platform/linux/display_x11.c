#include "include/display_x11.h"

#include "core/error_list.h"
#include "core/logger.h"

sshort16 displayx11_setup(DisplayX11 *display_x11)
{
    DisplayX11 *w = (DisplayX11 *) display_x11;

    // Open display
    w->display = XOpenDisplay(NULL);
    if(w->display == NULL)
    {
        LF_FATAL(ERR_WINDOW, "Cannot open X display.");
        return ERR_WINDOW;
    }

    // Setup screen
    w->screen = DefaultScreenOfDisplay(w->display);
    w->screen_id = DefaultScreen(w->display);

    return OK;
}

sshort16 displayx11_create(DisplayX11 *display_x11, const char *title,
                uint32 x, uint32 y, uint32 width, uint32 height)
{
    DisplayX11 *w = (DisplayX11 *) display_x11;

    // Create and open Window
    w->x_window_attribs.border_pixel = BlackPixel(w->display, w->screen_id);
    w->x_window_attribs.background_pixel = WhitePixel(w->display, w->screen_id);
    w->x_window_attribs.override_redirect = True;
    w->x_window_attribs.colormap = XCreateColormap(w->display, RootWindow(w->display, w->screen_id), w->visual->visual, AllocNone);
    w->x_window_attribs.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask | KeymapStateMask
                                     | StructureNotifyMask | ButtonPressMask | ButtonReleaseMask
                                     | EnterWindowMask | LeaveWindowMask | PointerMotionMask
                                     | FocusChangeMask;
    w->id = XCreateWindow(
            w->display,
            RootWindow(w->display, w->screen_id),
            x,
            y,
            width,
            height,
            0,
            w->visual->depth,
            InputOutput,
            w->visual->visual,
            CWBackPixel | CWColormap | CWBorderPixel | CWEventMask,
            &w->x_window_attribs);
    
    if(w->id == 0)
    {
        LF_FATAL(ERR_WINDOW, "Failed to create window.");
        XCloseDisplay(w->display);
        return ERR_WINDOW;
    }

    // TODO: XWindowAttribs and XSelectInput? refactor
    // Set Input
    XSelectInput(w->display, w->id, ExposureMask | KeyPressMask | KeyReleaseMask | KeymapStateMask
                                    | StructureNotifyMask | ButtonPressMask | ButtonReleaseMask
                                    | EnterWindowMask | LeaveWindowMask | PointerMotionMask
                                    | FocusChangeMask);

    // Name the Window
    XStoreName(w->display, w->id, title);

    // Show the window
	XClearWindow(w->display, w->id);
	XMapRaised(w->display, w->id);

    // Redirect Close
	w->delete_msg = XInternAtom(w->display, "WM_DELETE_WINDOW", False);
	XSetWMProtocols(w->display, w->id, &w->delete_msg, 1);

    return OK;
}

void displayx11_show(DisplayX11 *display_x11)
{
    DisplayX11 *w = (DisplayX11 *) display_x11;

    // Show the window
	XClearWindow(w->display, w->id);
	XMapRaised(w->display, w->id);
}


void displayx11_destroy(DisplayX11 *display_x11, struct GLContext *gl_context)
{
    DisplayX11 *w = (DisplayX11 *) display_x11;
    // GLContext *glc = (GLContext *) context;
    (void)gl_context;
}