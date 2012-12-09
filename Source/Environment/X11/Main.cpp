#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glxext.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../Skeleton/Skeleton.h"

static void initGL(Display *dpy, Window *winRet, GLXContext *ctxRet)
{
    /* GL init */
    int attribs[] = { GLX_RGBA,
                      GLX_RED_SIZE, 1,
                      GLX_GREEN_SIZE, 1,
                      GLX_BLUE_SIZE, 1,
                      GLX_DOUBLEBUFFER,
                      GLX_DEPTH_SIZE, 1,
                      None };

    int scrnum = DefaultScreen(dpy);
    Window root = RootWindow(dpy, scrnum );
    XVisualInfo *visinfo = glXChooseVisual(dpy, scrnum, attribs);
    GLXContext ctx = NULL;

    /* Window init */

    XSetWindowAttributes attr;
    Window win;

    attr.background_pixel = 0;
    attr.colormap = XCreateColormap( dpy, root, visinfo->visual, AllocNone);
    attr.event_mask = StructureNotifyMask;

    win = XCreateWindow( dpy, root, 15, 15, 640, 480, 0, visinfo->depth,
                         InputOutput, visinfo->visual,
                         CWBackPixel | CWColormap | CWEventMask,
                         &attr);

    XSizeHints sizehints;

    sizehints.x = 15;
    sizehints.y = 15;
    sizehints.width  = 640;
    sizehints.height = 480;
    sizehints.flags = USSize;
    XSetNormalHints(dpy, win, &sizehints);
    XSetStandardProperties(dpy, win, "nBody", "nBody",
                           None, (char **)NULL, 0, &sizehints);

    ctx = glXCreateContext( dpy, visinfo, NULL, True );

    if (!ctx) {
        printf("Error: glXCreateContext failed\n");
        exit(1);
    }

    *winRet = win;
    *ctxRet = ctx;
}



int
main(int argc, char *argv[])
{
    Display *dpy;
    Window win;
    GLXContext ctx;

    CSkeleton::PreInit();

    dpy = XOpenDisplay(NULL);
    initGL(dpy, &win, &ctx);
    XMapWindow(dpy, win);
    glXMakeCurrent(dpy, win, ctx);

    CSkeleton::PostInit();


    // main event loop

    while(true)
    {
        // Execute code in idle
        bool Repeat = false;
        bool Exit = false;

        switch(CSkeleton::Run())
        {
        // Exit application
        case CSkeleton::rmExit:
            Exit = true;
            break;

        // Repeat without processing any massages
        case CSkeleton::rmRepeat:
            Repeat = true;
            break;

        // Process all messages and continue execution
        case CSkeleton::rmContinue:
        case CSkeleton::rmGoForIdle:
            break;
        }

        if(Exit)
            break;

        if(Repeat)
            continue;

        glXSwapBuffers(dpy, win);

        // Process all available messages
        while(XPending(dpy) > 0)
        {
            XEvent event;
            XNextEvent(dpy, &event);
            if (event.type == ConfigureNotify) {
                CSkeleton::Resize(event.xconfigure.width, event.xconfigure.height);
                continue;
            }
        }
    }
    CSkeleton::PreDeinit();

    glXMakeCurrent(dpy, None, NULL);
    glXDestroyContext(dpy, ctx);
    XDestroyWindow(dpy, win);
    XCloseDisplay(dpy);
    // Execute post-deinitialization function
    CSkeleton::PostDeinit();

}
