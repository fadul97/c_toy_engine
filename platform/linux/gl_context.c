#include "include/gl_context.h"

#include "include/display_x11.h"
#include "core/logger.h"
#include "core/error_list.h"
#include <string.h>

b8 is_extension_supported(const char *ext_list, const char *extension);

sshort16 glcontext_create(GLContext *context, DisplayX11 *display_x11)
{
    GLContext *glc = (GLContext *) context;
    DisplayX11 *w = (DisplayX11 *) display_x11;

    // Check GLX version
    int major_glx = 0;
    int minor_glx = 0;
    glXQueryVersion(w->display, &major_glx, &minor_glx);
    if(major_glx <= 1 && minor_glx < 2)
    {
        LF_FATAL(ERR_CONTEXT, "GLX 1.2 or greater is required. Current version: %d.%d.", major_glx, minor_glx);
        XCloseDisplay(w->display);
        return ERR_CONTEXT;
    }

    LF_INFO("Current GLX version: %d.%d", major_glx, minor_glx);
    LF_INFO("GLX client version: %s", glXGetClientString(w->display, GLX_VERSION));
    LF_INFO("GLX client vendor: %s", glXGetClientString(w->display, GLX_VENDOR));
    // LF_INFO("GLX client extensions: %s\t", glXGetClientString(w->display, GLX_EXTENSIONS));

    LF_INFO("GLX server version: %s", glXQueryServerString(w->display, w->screen_id, GLX_VERSION));
    LF_INFO("GLX server vendor: %s", glXQueryServerString(w->display, w->screen_id, GLX_VENDOR));
    // LF_INFO("GLX server extensions: %s\t ", glXQueryServerString(w->display, w->screen_id, GLX_EXTENSIONS));

    // GLX, create XVisualInfo, this is the minimum visuals we want for a Modern OpenGL context
    GLint glx_attribs[] = {
        GLX_X_RENDERABLE,   True,
		GLX_DRAWABLE_TYPE,  GLX_WINDOW_BIT,
		GLX_RENDER_TYPE,    GLX_RGBA_BIT,
		GLX_X_VISUAL_TYPE,  GLX_TRUE_COLOR,
		GLX_RED_SIZE,       8,
		GLX_GREEN_SIZE,     8,
		GLX_BLUE_SIZE,      8,
		GLX_ALPHA_SIZE,     8,
		GLX_DEPTH_SIZE,     24,
		GLX_STENCIL_SIZE,   8,
		GLX_DOUBLEBUFFER,   True,
		None
    };
    
    int fb_count;
	GLXFBConfig* fbc = glXChooseFBConfig(w->display, w->screen_id, glx_attribs, &fb_count);
	if(fbc == 0)
    {
		LF_FATAL(ERR_CONTEXT, "Failed to retrieve framebuffer.");
		XCloseDisplay(w->display);
		return ERR_CONTEXT;
	}
	LF_DEBUG("Found %d matching framebuffers.", fb_count);

    // Pick the FB config/visual with the most samples per pixel
	LF_DEBUG("Getting best XVisualInfo");
	int best_fbc = -1, worst_fbc = -1, best_num_samp = -1, worst_num_samp = 999;
	for (int i = 0; i < fb_count; ++i)
    {
		XVisualInfo *temp_vi = glXGetVisualFromFBConfig(w->display, fbc[i] );
		if (temp_vi != 0)
        {
			int samp_buf;
            int samples;

            glXGetFBConfigAttrib(w->display, fbc[i], GLX_SAMPLE_BUFFERS, &samp_buf);
			glXGetFBConfigAttrib(w->display, fbc[i], GLX_SAMPLES       , &samples);

            //std::cout << "  Matching fbconfig " << i << ", SAMPLE_BUFFERS = " << samp_buf << ", SAMPLES = " << samples << ".";

			if(best_fbc < 0 || (samp_buf && samples > best_num_samp))
            {
				best_fbc = i;
				best_num_samp = samples;
			}

			if(worst_fbc < 0 || !samp_buf || samples < worst_num_samp)
				worst_fbc = i;

			worst_num_samp = samples;
		}
		XFree(temp_vi);
	}

    LF_DEBUG("Best visual info index: %d.", best_fbc);
    glc->fb_config = fbc[best_fbc];
    XFree(fbc);

    w->visual = glXGetVisualFromFBConfig(w->display, glc->fb_config);
    if(w->visual == 0)
    {
        LF_FATAL(ERR_CONTEXT, "Failed to create correct visual window.");
        XCloseDisplay(w->display);
        return ERR_CONTEXT;
    }

    if(w->screen_id != w->visual->screen)
    {
		LF_FATAL(ERR_CONTEXT, "screen_id(%d) does not match visual->screen(%d).", w->screen_id, w->visual->screen);
		XCloseDisplay(w->display);
		return ERR_CONTEXT;
	}

	return OK;
}

sshort16 glcontext_make_current(GLContext *context, DisplayX11 *display_x11)
{
    GLContext *glc = (GLContext *) context;
    DisplayX11 *w = (DisplayX11 *) display_x11;

    // Create GLX OpenGL Context
    glXCreateContextAttribsARBProc glXCreateContextAttribsARB = 0;
	glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc) glXGetProcAddressARB((const GLubyte *) "glXCreateContextAttribsARB");

    const char *glx_exts = glXQueryExtensionsString(w->display, w->screen_id);
	// LF_INFO("Late extensions: %s\t", glx_exts);
	if(glXCreateContextAttribsARB == 0)
		LF_ERROR(ERR_CONTEXT, "glXCreateContextAttribsARB() not found.");

    int context_attribs[] = {
		GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
		GLX_CONTEXT_MINOR_VERSION_ARB, 2,
		GLX_CONTEXT_FLAGS_ARB, GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
		None
	};

    glc->context = 0;
    if(!is_extension_supported(glx_exts, "GLX_ARB_create_context"))
		glc->context = glXCreateNewContext(w->display, glc->fb_config, GLX_RGBA_TYPE, 0, True);
	else
		glc->context = glXCreateContextAttribsARB(w->display, glc->fb_config, 0, TRUE, context_attribs);
	XSync(w->display, False);

    // Verifying that context is a direct context
	if(!glXIsDirect(w->display, glc->context)) {
		LF_INFO("Indirect GLX rendering context obtained");
	}
	else {
		LF_INFO("Direct GLX rendering context obtained");
	}

    glXMakeCurrent(w->display, w->id, glc->context);

	int version = gladLoadGL((void*)glXGetProcAddress);
    LF_INFO("Current GL loaded: %d.%d", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

	LF_INFO("GL Renderer: %s", glGetString(GL_RENDERER));
	LF_INFO("GL Version: %s", glGetString(GL_VERSION));
	LF_INFO("GLSL Version: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));

	return OK;
}

void glcontext_destroy(GLContext *context, DisplayX11 *display_x11)
{
    GLContext *glc = (GLContext *) context;
    DisplayX11 *w = (DisplayX11 *) display_x11;

    // Cleanup GLX
	glXDestroyContext(w->display, glc->context);
}

b8 is_extension_supported(const char *ext_list, const char *extension){
	const char *start;
	const char *where, *terminator;

	/* Extension names should not have spaces. */
	where = strchr(extension, ' ');
	if (where || *extension == '\0')
	return FALSE;

	/* It takes a bit of care to be fool-proof about parsing the
	 OpenGL extensions string. Don't be fooled by sub-strings,
	 etc. */
	for (start=ext_list;;) {
	where = strstr(start, extension);

	if (!where) {
	 	break;
	}

	terminator = where + strlen(extension);

	if ( where == start || *(where - 1) == ' ' ) {
		if ( *terminator == ' ' || *terminator == '\0' ) {
			return TRUE;
		}
	}	

	start = terminator;
	}

	return FALSE;
}