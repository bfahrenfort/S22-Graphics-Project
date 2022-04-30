#include "Part1.hpp"
#include "globals.h"
#include "vector/vec_2.hpp"

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
#endif // XCODE_SET_IN_GLOBALS

#include <vector>

int p1_window_id = -1;

// Point acquiring utilities
static bool acquired_points = false;
static int fuzz = 5;
static bool modifier_button = true;
static bool shift_down = false;


// Transformation utilities
static std::vector<Vec2<GLint>> polygon_points{ };
static Vec2<GLfloat> cur_translate(0, 0), cur_scale(1, 1);
static GLfloat rotTheta{ };

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

// Update the display
static void p1_display()
{
    glClearColor (1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    if (acquired_points) // draw the polygon
    {
        glPushMatrix();
        glColor3f(red, green, blue);
        glTranslatef(cur_translate.x, cur_translate.y, 1.0);
        glRotatef(rotTheta, 0, 0, 1.0);
        glScalef(cur_scale.x, cur_scale.y, 1.0);

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
    glutPostRedisplay();
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
                    if (polygon_points.size() > 1 && point_fuzz(x, y, polygon_points.at(0))) // We've completed the polygon
                    {
                        acquired_points = true;
                        glutIdleFunc(p1_idle);
                    }
                    else // Add this point and go again
                    {
                        polygon_points.push_back(Vec2<GLint>(x, y)); 
                        glutPostRedisplay();
                    }
                }
                else // Handle translate/scale/reverse
                {
                    // Translate:
                    if (action == GLUT_DOWN)
                        cur_translate.x = 10;
                        cur_translate.y = 20;
                        
                        
                    
                    // Get modifiers
                mods = glutGetModifiers();
                    if (mods & GLUT_ACTIVE_SHIFT)
                    {
                        shift_down = true;
                        cur_scale.x = 1;
                        cur_scale.y = 2;
                    }
                    else if (mods & GLUT_ACTIVE_ALT)
                    {
                        // stuff for roatate
                    }

                    // Set boolean for shift and ctrl
                    //shift_key = true;
                    //ctrl_key = true;
                    
                }
                
            }
            else if(action == GLUT_UP)
            {
                shift_down  = false;
            }
            break;
        case GLUT_RIGHT_BUTTON: // Stop the program
            if (action == GLUT_DOWN)
            {
                if(p2_window_id < 0)
                    exit(0);
                else
                {
                    p1_window_id = -1;
                    glutIdleFunc(NULL);
                    glutDestroyWindow(p1_window_id);
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

    gluOrtho2D (0, p1_window_width, p1_window_height, 0);
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
    //glutPassiveMotionFunc(p1_mouse);
}
