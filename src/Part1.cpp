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

// Point acquiring utilities
bool acquired_points = false;
int fuzz = 40;

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

bool point_fuzz(GLint x, GLint y, Vec2<GLint> point)
{
    if(x < point.x + fuzz && x > point.x - fuzz && y < point.y + fuzz && y > point.y - fuzz)
        return true;

    return false;
}

void init()
{
    // TODO: acquire polygon points

    party();
}

void p1_display()
{
    glClearColor (1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    if (acquired_points)
    {
        std::cout << "displaying" << std::endl;
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

    glutSwapBuffers();
    glFlush();
}

void p1_idle()
{
    glutPostRedisplay();
}

void p1_mouse(GLint button, GLint action, GLint x, GLint y)
{
    switch (button) {
        case GLUT_LEFT_BUTTON: // Start the rotation.
            if (action == GLUT_DOWN)
            {
                if(!acquired_points) // keep accepting points
                {
                    if (polygon_points.size() > 1 && point_fuzz(x, y, polygon_points.at(0)))
                    {
                        acquired_points = true;
                        glutIdleFunc(p1_idle);
                    }
                    else
                        polygon_points.push_back(Vec2<GLint>(x, y));
                }
                else
                {
                    // get modifiers and translate or scale
                }
            }
            break;
        case GLUT_RIGHT_BUTTON: // Stop the rotation.
            if (action == GLUT_DOWN)
            {
                if(p2_window_id < 0)
                    exit(0);
                else
                {
                    p1_window_id = -1;
                    glutDestroyWindow(p1_window_id);
                }
            }
            break;
        default:
            break;
    }
}

static void p1_reshape (GLint newWidth, GLint newHeight)
{
    p1_window_width = newWidth;
    p1_window_height = newHeight;
    //update_positions();
    glViewport (0, 0, (GLsizei) newWidth, (GLsizei) newHeight);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ( );

    gluOrtho2D (-p1_window_width/2, p1_window_width/2, -p1_window_height/2, p1_window_height/2);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ( );
    glClear (GL_COLOR_BUFFER_BIT);
}

void Part1::runPart1()
{
    initrand();
    init();
    p1_window_id = glutCreateWindow("Part 1");
    glutDisplayFunc(p1_display);
    glutReshapeFunc (p1_reshape);
    glutIdleFunc(nullptr);
    glutMouseFunc(p1_mouse);
}