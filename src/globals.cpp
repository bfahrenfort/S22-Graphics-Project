#include "globals.h"

#include <ctime>
#include <random>
#include <numbers>

#ifdef XCODE_SET_IN_GLOBALS
    #define GL_SILENCE_DEPRECATION
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#else
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif

void initrand()
{
    srand(time(nullptr)); // Yes, time is bad as a seed. This is for colors only.
}

float randf()
{
    return (float) std::rand() / (float) RAND_MAX;
}

using std::numbers::pi;
void regular_polygon_points(double radius, int num_verts)
{
    double angle = 0.0;

    for(int i = 0; i < num_verts; ++i)
    {
        // Angle of the next point, rotated so the first point is on top in the shapes that it should be
        angle = 2 * pi / num_verts * i + pi/(num_verts % 2 == 0 ? num_verts : 2);

        glVertex3d(radius * cos(angle), radius * sin(angle), 0);
    }
}