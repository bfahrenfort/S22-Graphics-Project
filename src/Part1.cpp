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
static bool acquired_points = false;
static int fuzz = 8;

// Transformation utilities
static std::vector<Vec2<GLint>> polygon_points{ };
static Vec2<GLfloat> cur_translate(0, 0), cur_scale(1, 1);
static GLfloat rotTheta = 0.0;
static GLint rotMultiplier = 1;
static GLfloat rotBase = 0.4;
bool scale = false, translate = false;

// Color
static GLfloat red{ }, green{ }, blue{ };
void party()
{
    red = randf();
    green = randf();
    blue = randf();
}

// Check if an X and Y are within fuzz range of a preexisting point
static bool point_fuzz(GLint x, GLint y, Vec2<GLint> point)
{
    if(x < point.x + fuzz && x > point.x - fuzz && y < point.y + fuzz && y > point.y - fuzz)
        return true;

    return false;
}

// Setup the environment
static void init()
{
    party();
}

float avgofArrayx(std::vector<Vec2<GLint>>polygon_pointsx) {
    float a = 0.0;
    for (int i = 0; i < polygon_pointsx.size(); ++i) {
        a = polygon_pointsx[i].x + a;
    }
    a = a / polygon_pointsx.size();
    return a;
}

float avgofArrayy(std::vector<Vec2<GLint>>polygon_pointsy) {
    float a = 0.0;
    for (int i = 0; i < polygon_pointsy.size(); ++i) {
        a = polygon_pointsy[i].y + a;
    }
    a = a / polygon_pointsy.size();
    return a;
}

// Update the display
static void p1_display()
{
    glClearColor (1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    if (acquired_points) // draw the polygon
    {
        glPushMatrix();

        // 6: color
        glColor3f(red, green, blue);

        // 5: Translate back to desired position
        glTranslated(cur_translate.x, cur_translate.y, 0);

        // 4: scale
        glScalef(cur_scale.x, cur_scale.y, 1.0);

        // 2: rotate around Z axis
        glRotatef(rotTheta, 0, 0, 1);

        // 1: translate to origin
        glTranslated(-avgofArrayx(polygon_points), -avgofArrayy(polygon_points), 0);

        glBegin(GL_POLYGON);
        for(Vec2<GLint> p : polygon_points)
            glVertex2i(p.x, p.y);
        glEnd();

        glPopMatrix();
    }
    else // Draw points we've done so far
    {
        bool first = true;
        Vec2<GLint> current;
        for(int i = 0; i < polygon_points.size(); ++i)
        {
            current = polygon_points.at(i);
            glPushMatrix();
            glColor3f(first ? 1.0 : 0, 0, first ? 0 : 1.0); // First point is special
            glTranslatef(current.x, current.y, 0); // Center around the point

            // Simple circle
            glBegin(GL_POLYGON);
            regular_polygon_points(fuzz, 16);
            glEnd();

            glPopMatrix();
            first = false;
        }
    }
    glutSwapBuffers();
    glFlush();
}
// While idle, rotate
static void p1_idle()
{
    rotTheta += rotBase * rotMultiplier;
    if(rotTheta > 360.0)
        rotTheta -= 360.0;

    glutPostRedisplay();
}

void p1_motion(int x, int y)
{
    if (translate)
    {
        cur_translate.x = x;
        cur_translate.y = y;
    }

    if (scale)
    {
        cur_scale.x = abs((x - cur_translate.x) / 50);
        cur_scale.y = abs((y - cur_translate.y) / 50);
    }
}

// Handle mouse clicks
static void p1_mouse(GLint button, GLint action, GLint x, GLint y)
{
    int mods;
    switch (button) {
        case GLUT_LEFT_BUTTON:
            if (action == GLUT_DOWN)
            {
                if(!acquired_points) // keep accepting points
                {
                    if (polygon_points.size() > 2 && point_fuzz(x, y, polygon_points.at(0))) // We've completed the polygon
                    {
                        acquired_points = true;
                        cur_translate.x = avgofArrayx(polygon_points);
                        cur_translate.y = avgofArrayy(polygon_points);
                        glutIdleFunc(p1_idle);
                    }
                    else // Add this point and go again
                    {
                        polygon_points.emplace_back(x, y);
                        glutPostRedisplay();
                    }
                }
                else // Handle translate/scale/reverse
                {
                    mods = glutGetModifiers();

                    if (mods & GLUT_ACTIVE_SHIFT) // Scale the object
                    {
                        scale = true;
                        translate = false;
                    }
                    else if (mods & GLUT_ACTIVE_ALT) { // Swap rotation
                        rotMultiplier *= -1;
                        party();
                    }
                    else // Translate the object
                    {
                        translate = true;
                        scale = false;
                    }
                }
            }
            else if (action == GLUT_UP)
            {
                translate = false;
                scale = false;
            }
            break;
        case GLUT_RIGHT_BUTTON: // Stop the program
            if (action == GLUT_DOWN)
            {
                if(p2_window_id < 0)
                    exit(0);
                else
                {
                    int p1wid = p1_window_id;
                    p1_window_id = -1;
                    glutIdleFunc(nullptr);
                    glutDestroyWindow(p1wid);
                }
            }
            break;
        default:
            break;
    }
}

// Resize the window
static void p1_reshape (GLint newWidth, GLint newHeight)
{
    p1_window_width = newWidth;
    p1_window_height = newHeight;
    glViewport (0, 0, (GLsizei) newWidth, (GLsizei) newHeight);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ( );

    gluOrtho2D(0, p1_window_width, p1_window_height, 0);
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
    glutMotionFunc(p1_motion);
}