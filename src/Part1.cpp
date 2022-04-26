#include "Part1.hpp"
#include "globals.h"
#include "vector/vec_2.hpp"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif // __APPLE__

#ifdef XCODE_SET_IN_GLOBALS
    #define GL_SILENCE_DEPRECATION
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#else
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif // XCODE_SET_IN_GLOBALS

int p1_window_id = -1;
