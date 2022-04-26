#include <numbers>

#include "Part2.hpp"
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

GLuint listMove; // Define name for display list.
GLfloat red = 0, green = 0, blue = 0;
int p2_window_id = -1;

// Animation calculations
const int poly_radius = 60;
static GLfloat rotTheta = 0.0;
static GLfloat rotMultiplier = 1.0;
static Vec2<GLint> left_pos;
static Vec2<GLint> right_pos;
static Vec2<GLint> cur_pos;
static bool movingLeft = false;

void update_positions()
{
    left_pos = Vec2<GLint>((-p2_window_width/2) + poly_radius, (-p2_window_height/2) + poly_radius);
    right_pos = Vec2<GLint>((p2_window_width/2) - poly_radius, (p2_window_height/2) + poly_radius);
}

// Ignore this
void rave(void)
{
    red = randf();
    green = randf();
    blue = randf();
}

// Create a collection of points equiangular
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

static void init (void)
{
    // Initialize vectors and colors
    update_positions();
    cur_pos = Vec2<GLint>(left_pos);
    red = randf();
    green = randf();
    blue = randf();
    glClearColor (1.0, 1.0, 1.0, 0.0);
    glColor3f (red, green, blue);

    listMove = glGenLists (1);
    glNewList (listMove, GL_COMPILE);

    // Draw our circle
    glBegin (GL_POLYGON);
    regular_polygon_points(poly_radius, 16);
    glEnd ( );
    glEndList ( );
}

void displayHex (void)
{
    auto temp_pos(cur_pos);
    glClear (GL_COLOR_BUFFER_BIT);

    // Perform appropriate transforms
    glPushMatrix ( );
    glColor3f (red, green, blue);
    glTranslated(temp_pos.x, temp_pos.y, 0);
    glRotatef (rotTheta, 0, 0, 1.0);
    glTranslated(0, 0, 0);

    // Draw and commit to screen
    glCallList (listMove);
    glPopMatrix ( );
    glutSwapBuffers ( );
    glFlush ( );
}

void move ()
{
    // Move the ball
    cur_pos.x = cur_pos.x + 3.0 * rotMultiplier * (movingLeft ? -1 : 1);
    cur_pos.y = poly_radius - p2_window_height/2;

    // Swap directions if needed
    bool t_movingLeft = movingLeft;
    if (cur_pos.x > right_pos.x)
        movingLeft = true;
    else if (cur_pos.x < left_pos.x)
        movingLeft = false;

    // Party
    if (t_movingLeft != movingLeft)
        rave();

    // Rotate the ball
    rotTheta += 3.0 * rotMultiplier * (movingLeft ? 1 : -1);
    if (rotTheta > 360.0)
        rotTheta -= 360.0;

    glutPostRedisplay ( );
}

void mouseFcn (GLint button, GLint action, GLint x, GLint y)
{
    switch (button) {
        case GLUT_LEFT_BUTTON: // Start the rotation.
            if (action == GLUT_DOWN)
            {
                rotMultiplier = 1.0;
                glutIdleFunc(move);
            }
            break;
        case GLUT_RIGHT_BUTTON: // Stop the rotation.
            if (action == GLUT_DOWN)
            {
                if(p1_window_id < 0)
                    exit(0);
                else
                {
                    p2_window_id = -1;
                    glutDestroyWindow(p2_window_id);
                }
            }
            break;
        default:
            break;
    }
}


void winReshapeFcn (GLint newWidth, GLint newHeight)
{
    p2_window_width = newWidth;
    p2_window_height = newHeight;
    update_positions();
    glViewport (0, 0, (GLsizei) newWidth, (GLsizei) newHeight);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ( );

    gluOrtho2D (-p2_window_width/2, p2_window_width/2, -p2_window_height/2, p2_window_height/2);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ( );
    glClear (GL_COLOR_BUFFER_BIT);
}

void Part2::runPart2()
{
    initrand();
    glutCreateWindow("Part 2");
    init ( );
    glutDisplayFunc (displayHex);
    glutReshapeFunc (winReshapeFcn);
    glutMouseFunc (mouseFcn);
}