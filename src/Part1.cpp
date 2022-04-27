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

#include <vector>

int p1_window_id = -1;

bool acquired_points = false;

// Transformation utilities
std::vector<Vec2<GLint>> polygon_points{ };
Vec2<GLfloat> cur_translate, cur_scale{ };
GLfloat rotTheta{ };

// Color
static GLfloat red{ }, green{ }, blue{ };

void party()
{
    red = randf();
    green = randf();
    blue = randf();
}

void init()
{
    // TODO: acquire polygon points

    glClearColor (1.0, 1.0, 1.0, 0.0);
    party();
}

void p1_display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    if (acquired_points)
    {
        glPushMatrix();
        glColor3f(red, green, blue);
        glTranslatef(cur_translate.x, cur_translate.y, 1.0);
        glRotatef(rotTheta, 0, 0, 1.0);
        glScalef(cur_scale.x, cur_scale.y, 0);

        glBegin(GL_POLYGON);
        for(Vec2<GLint> p : polygon_points)
            glVertex2i(p.x, p.y);
        glEnd();

        glPopMatrix();
    }
}


void Part1::runPart1()
{
    initrand();
    init();
    p1_window_id = glutCreateWindow("Part 1");
    glutDisplayFunc(p1_display);
    //glutReshapeFunc (winReshapeFcn);
    //glutMouseFunc (mouseFcn);
}