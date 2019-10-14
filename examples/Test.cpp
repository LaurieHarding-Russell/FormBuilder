#include<stdio.h>
#include<stdlib.h>
#include<X11/Xlib.h>
#include<GL/gl.h>
#include<GL/glx.h>
#include<GL/glu.h>

#include "examples/TestComponent/TestComponent.h"

void initializeX11(Display *display, Window root, XVisualInfo *visualInfo, Window myWindow);

int main() {
       // FIXME, yucky
       Display                 *display;
       Window                  root;
       XVisualInfo             *visualInfo;
       Window                  myWindow;
       GLXContext              glContext;
       XWindowAttributes       snapshotWindowAttributes;
       XEvent                  x11Event;

       glContext = glXCreateContext(display, visualInfo, NULL, GL_TRUE);
       glXMakeCurrent(display, myWindow, glContext);
 
       TestComponent* test = new TestComponent();

       while(1) {
              XNextEvent(display, &x11Event);

              if(x11Event.type == Expose) {
                     XGetWindowAttributes(display, myWindow, &snapshotWindowAttributes);
                     test->render();
                     glViewport(0, 0, snapshotWindowAttributes.width, snapshotWindowAttributes.height);
                     glXSwapBuffers(display, myWindow);
              } else if(x11Event.type == KeyPress) {
                     glXMakeCurrent(display, None, NULL);
                     glXDestroyContext(display, glContext);
                     XDestroyWindow(display, myWindow);
                     XCloseDisplay(display);
                     exit(0);
              }
       }
}

void initializeX11(Display *display, Window root, XVisualInfo *visualInfo, Window myWindow) {
       GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
       XSetWindowAttributes defaultWindowAttributes;

       display = XOpenDisplay(NULL);

       if(display == NULL) {
              printf("\n\tcannot connect to X server\n\n");
              exit(0);
       }

       root = DefaultRootWindow(display);

       visualInfo = glXChooseVisual(display, 0, att);

       if(visualInfo == NULL) {
              printf("\n\tno appropriate visual found\n\n");
              exit(0);
       }
       else {
              printf("\n\tvisual %p selected\n", (void *)visualInfo->visualid);
       }


       Colormap colourMap = XCreateColormap(display, root, visualInfo->visual, AllocNone);

       defaultWindowAttributes.colormap = colourMap;
       defaultWindowAttributes.event_mask = ExposureMask | KeyPressMask;

       myWindow = XCreateWindow(display, root, 0, 0, 600, 600, 0, visualInfo->depth, InputOutput, visualInfo->visual, CWColormap | CWEventMask, &defaultWindowAttributes);

       XMapWindow(display, myWindow);
       XStoreName(display, myWindow, "Test Form");

}
