#include <GL/gl.h>
#include <GL/glu.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif // __APPLE__

#include "Part1.hpp"
#include "globals.h"
#include "vector/vec_2.hpp"

int p1_window_id = -1;