#include <GL/gl.h>
#include <GL/glu.h>

#ifdef XCODE_SET_IN_GLOBALS
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#else
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif // XCODE_SET_IN_GLOBALS
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif // __APPLE__

#include "Part2.hpp"
#include "globals.h"
#include "vector/vec_2.hpp"

GLuint listMove; // Define name for display list.
GLfloat red = 0, green = 0, blue = 0;
int p2_window_id = -1;

// Animation calculations
const int radius = 60;
static GLfloat rotTheta = 0.0;
static GLfloat rotMultiplier = 1.0;
Vec2<GLint> left_pos((-p2_window_width/2) + radius, (-p2_window_height/2) + radius);
Vec2<GLint> right_pos((p2_window_width/2) - radius, (p2_window_height/2) + radius);
Vec2<GLint> cur_pos;

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
    cur_pos = Vec2<GLint>(left_pos);
    red = randf();
    green = randf();
    blue = randf();
    glClearColor (1.0, 1.0, 1.0, 0.0);
    glColor3f (red, green, blue);
/* Set up a display list for a red regular hexagon.
* Vertices for the hexagon are six equally spaced
* points around the circumference of a circle.
*/
    listMove = glGenLists (1); //Generates a continuous range of empty display lists. Display lists are groups of GL commands that have been stored for subsequent execution.

    glNewList (listMove, GL_COMPILE); //Specifies the display-list name.

    // set the current color

// The origin three-dimensional screen coordinates is placed at the center of the display window
// so that the z axis passes through this center position


/*In procedure init, we use a display list to set up the description of the regular hexagon, whose
center position is originally at the screen-coordinate position (150, 150) with a
radius (distance from the polygon center to any vertex) of 100 pixels.*/

    glPushMatrix();
    glTranslated(left_pos.x, left_pos.y, 0);
    glBegin (GL_POLYGON);
    regular_polygon_points(radius, 16);
    glEnd ( );
    glEndList ( );
}


/*In the display function, displayHex, specify an initial 0◦ rotation about the z axis
and invoke the glutSwapBuffers routine */


void displayHex (void)
{
    glClear (GL_COLOR_BUFFER_BIT);
    glPushMatrix ( );  //push and pop the current matrix stack.
    rave();
    glColor3f (red, green, blue);
    glRotatef (rotTheta, 0.0, 0.0, 1.0);
    glCallList (listMove); // execute a display list
    glPopMatrix ( ); // pops the current matrix stack, replacing the current matrix with the one below it on the stack.
    glutSwapBuffers ( );
    glFlush ( );
}

void move ()
{
    rotTheta += 3.0 * rotMultiplier;
    if (rotTheta > 360.0)
        rotTheta -= 360.0;
    glutPostRedisplay ( ); // marks the current window as needing to be redisplayed . The next iteration through glutMainLoop, the window's display callback will be called to redisplay the window's normal plane
}

/*The calculation of the incremented rotation
angle is performed in procedure rotateAntiClockwise, which is called by the
glutIdleFunc routine in procedure mouseFcn */


void mouseFcn (GLint button, GLint action, GLint x, GLint y)
{
    switch (button) {
        case GLUT_LEFT_BUTTON: // Start the rotation.
            if (action == GLUT_DOWN)
            {
                rotMultiplier = 1.0;
                glutIdleFunc(move); // glutIdleFunc sets the global idle callback to be func so a GLUT program can perform background processing tasks or continuous animation when window system events are not being received
            }
            break;
        case GLUT_RIGHT_BUTTON: // Stop the rotation.
            if (action == GLUT_DOWN)
            {
                if(p1_window_id < 0)
                    exit(0);
                else
                {
                    int p2wid = p2_window_id;
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
    glViewport (0, 0, (GLsizei) newWidth, (GLsizei) newHeight);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ( );
    gluOrtho2D (-320.0, 320.0, -320.0, 320.0);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ( );
    glClear (GL_COLOR_BUFFER_BIT);
}

void Part2::runPart2()
{
    glutCreateWindow("Part 2");
    init ( );
    glutDisplayFunc (displayHex);
    glutReshapeFunc (winReshapeFcn);
    glutMouseFunc (mouseFcn);
}