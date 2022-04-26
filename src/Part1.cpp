#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif // __APPLE__

#include "Part1.hpp"
#include "globals.h"
#include "vector/vec_2.hpp"

int p1_window_id = -1;
