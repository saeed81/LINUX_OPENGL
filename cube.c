// -- Written in C -- //

#include<stdio.h>
#include<stdlib.h>
#include<X11/X.h>
#include<X11/Xlib.h>
#include<GL/gl.h>
#include<GL/glx.h>
#include<GL/glu.h>

Display                 *dpy;
Window                  root;
GLint                   att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
XVisualInfo             *vi;
Colormap                cmap;
XSetWindowAttributes    swa;
Window                  win;
GLXContext              glc;
XWindowAttributes       gwa;
XEvent                  xev;


//glMatrixMode(GL_PROJECTION);
//glLoadIdentity();
//gluPerspective(60.0, 4.0/3.0, 1, 40);

// Position camera at (4, 6, 5) looking at (0, 0, 0) with the vector
// <0, 1, 0> pointing upward.
//glMatrixMode(GL_MODELVIEW);
//glLoadIdentity();
//gluLookAt(4, 6, 5, 0, 0, 0, 0, 1, 0);

static void DrawAQuad() {
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glClearDepth(1.0f);


  float fovY  = 60.0f;
  float front = 1.0f;
  float back  = 40.0f;
  float ratio = 1.0f;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective (fovY, ratio, front, back);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
  gluLookAt(5.0, 10.0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  
  glBegin(GL_LINES);
  glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(10, 0, 0);
  glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 10, 0);
  glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, 10);
  glEnd();
  glFlush();
  

  glBegin(GL_QUADS);        // Draw The Cube Using quads                                                                                                                                                                                                                                
  glColor3f(0.0f,1.0f,0.0f);    // Color Blue                                                                                                                                                                                                                                           
  glVertex3f( 1.0f, 1.0f,-1.0f);    // Top Right Of The Quad (Top)                                                                                                                                                                                                                      
  glVertex3f(-1.0f, 1.0f,-1.0f);    // Top Left Of The Quad (Top)                                                                                                                                                                                                                       
  glVertex3f(-1.0f, 1.0f, 1.0f);    // Bottom Left Of The Quad (Top)                                                                                                                                                                                                                    
  glVertex3f( 1.0f, 1.0f, 1.0f);    // Bottom Right Of The Quad (Top)                                                                                                                                                                                                                   
  glColor3f(1.0f,0.5f,0.0f);    // Color Orange                                                                                                                                                                                                                                         
  glVertex3f( 1.0f,-1.0f, 1.0f);    // Top Right Of The Quad (Bottom)                                                                                                                                                                                                                   
  glVertex3f(-1.0f,-1.0f, 1.0f);    // Top Left Of The Quad (Bottom)                                                                                                                                                                                                                    
  glVertex3f(-1.0f,-1.0f,-1.0f);    // Bottom Left Of The Quad (Bottom)                                                                                                                                                                                                                 
  glVertex3f( 1.0f,-1.0f,-1.0f);    // Bottom Right Of The Quad (Bottom)                                                                                                                                                                                                                
  glColor3f(1.0f,0.0f,0.0f);    // Color Red                                                                                                                                                                                                                                            
  glVertex3f( 1.0f, 1.0f, 1.0f);    // Top Right Of The Quad (Front)                                                                                                                                                                                                                   
  glVertex3f(-1.0f, 1.0f, 1.0f);    // Top Left Of The Quad (Front)                                                                                                                                                                                                                     
  glVertex3f(-1.0f,-1.0f, 1.0f);    // Bottom Left Of The Quad (Front)                                                                                                                                                                                                                
  glVertex3f( 1.0f,-1.0f, 1.0f);    // Bottom Right Of The Quad (Front)                                                                                                                                                                                                                
  glColor3f(1.0f,1.0f,0.0f);    // Color Yellow                                                                                                                                                                                                                                      
  glVertex3f( 1.0f,-1.0f,-1.0f);    // Top Right Of The Quad (Back)                                                                                                                                                                                                                     
  glVertex3f(-1.0f,-1.0f,-1.0f);    // Top Left Of The Quad (Back)                                                                                                                                                                                                                      
  glVertex3f(-1.0f, 1.0f,-1.0f);    // Bottom Left Of The Quad (Back)                                                                                                                                                                                                                  
  glVertex3f( 1.0f, 1.0f,-1.0f);    // Bottom Right Of The Quad (Back)                                                                                                                                                                                                                  
  glColor3f(0.0f,0.0f,1.0f);    // Color Blue                                                                                                                                                                                                                                           
  glVertex3f(-1.0f, 1.0f, 1.0f);    // Top Right Of The Quad (Left)                                                                                                                                                                                                                     
  glVertex3f(-1.0f, 1.0f,-1.0f);    // Top Left Of The Quad (Left)                                                                                                                                                                                                                      
  glVertex3f(-1.0f,-1.0f,-1.0f);    // Bottom Left Of The Quad (Left)                                                                                                                                                                                                                   
  glVertex3f(-1.0f,-1.0f, 1.0f);    // Bottom Right Of The Quad (Left)                                                                                                                                                                                                                  
  glColor3f(1.0f,0.0f,1.0f);    // Color Violet                                                                                                                                                                                                                                        
  glVertex3f( 1.0f, 1.0f,-1.0f);    // Top Right Of The Quad (Right)                                                                                                                                                                                                                    
  glVertex3f( 1.0f, 1.0f, 1.0f);    // Top Left Of The Quad (Right)                                                                                                                                                                                                                     
  glVertex3f( 1.0f,-1.0f, 1.0f);    // Bottom Left Of The Quad (Right)                                                                                                                                                                                                                  
  glVertex3f( 1.0f,-1.0f,-1.0f);    // Bottom Right Of The Quad (Right)                                                                                                                                                                                                                
  
  glEnd();            // End Drawing The Cube             

  glFlush();



} 
 
int main(int argc, char *argv[]) {

  dpy = XOpenDisplay(NULL);
 
  if(dpy == NULL) {
    printf("\n\tcannot connect to X server\n\n");
    exit(0);
  }
        
  root = DefaultRootWindow(dpy);

  vi = glXChooseVisual(dpy, 0, att);

  if(vi == NULL) {
    printf("\n\tno appropriate visual found\n\n");
    exit(0);
  } 
  else {
    printf("\n\tvisual %p selected\n", (void *)vi->visualid); /* %p creates hexadecimal output like in glxinfo */
  }


  cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);

  swa.colormap = cmap;
  swa.event_mask = ExposureMask | KeyPressMask;
 
  win = XCreateWindow(dpy, root, 0, 0, 600, 600, 0, vi->depth, InputOutput, vi->visual, CWColormap | CWEventMask, &swa);

  XMapWindow(dpy, win);
  XStoreName(dpy, win, "VERY SIMPLE APPLICATION");
 
  glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
  glXMakeCurrent(dpy, win, glc);
 
  glEnable(GL_DEPTH_TEST); 
 
  while(1) {
    XNextEvent(dpy, &xev);
        
    if(xev.type == Expose) {
      XGetWindowAttributes(dpy, win, &gwa);
      glViewport(0, 0, gwa.width, gwa.height);
      DrawAQuad(); 
      glXSwapBuffers(dpy, win);
    }
                
    else if(xev.type == KeyPress) {
      glXMakeCurrent(dpy, None, NULL);
      glXDestroyContext(dpy, glc);
      XDestroyWindow(dpy, win);
      XCloseDisplay(dpy);
      exit(0);
    }
  } /* this closes while(1) { */
} /* this is the } which closes int main(int argc, char *argv[]) { */
