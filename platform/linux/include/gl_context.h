#ifndef GL_CONTEXT_H
#define GL_CONTEXT_H

#include "core/defines.h"
#include "display_x11.h"
#include <glad/gl.h>
#include <GL/glx.h>

typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int*);

typedef struct GLContext{
    GLXContext context;
    GLXFBConfig fb_config;
} GLContext;

sshort16 glcontext_create(GLContext *context, DisplayX11 *display_x11);
sshort16 glcontext_make_current(GLContext *context, DisplayX11 *display_x11);
void glcontext_destroy(GLContext *context, DisplayX11 *display_x11);

#endif // GL_CONTEXT_H