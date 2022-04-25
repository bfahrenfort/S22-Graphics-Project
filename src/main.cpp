#include "Part1.hpp"
#include "Part2.hpp"
#include "globals.h"

#ifdef XCODE_SET_IN_GLOBALS
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#else
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif
#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif // __APPLE__

int p1_window_width = 640;
int p1_window_height = 480;

int p2_window_width = 640;
int p2_window_height = 640;

int main(int argc, char **argv)
{
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(p1_window_width, p1_window_height);

    // Start part 1 window

    // Start part 2 window
    glutInitWindowPosition(700, 100);
    glutInitWindowSize(p2_window_width, p2_window_height);
    Part2::runPart2();

    glutMainLoop();
    return 0;
}