#include "Part1.hpp"
#include "Part2.hpp"
#include "globals.h"

#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION
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
#endif

int p1_window_width = 640;
int p1_window_height = 480;

int p2_window_width = 640;
int p2_window_height = 640;

int main(int argc, char **argv)
{
    // Initialize GLUT
    glutInit(&argc, argv);
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    // Start part 1 window
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(p1_window_width, p1_window_height);
    Part1::runPart1();

    // Start part 2 window
    glutInitWindowPosition(1000, 100);
    glutInitWindowSize(p2_window_width, p2_window_height);
    Part2::runPart2();

    glutMainLoop();
    return 0;
}
