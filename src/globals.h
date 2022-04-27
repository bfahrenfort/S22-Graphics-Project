#ifndef GRAPHICSGROUPPROJECT_GLOBALS_H
#define GRAPHICSGROUPPROJECT_GLOBALS_H

// Set this if using XCode
//#define XCODE_SET_IN_GLOBALS

extern int p1_window_width;
extern int p1_window_height;

extern int p2_window_width;
extern int p2_window_height;

extern int p1_window_id;
extern int p2_window_id;

// Seed rand()
void initrand();

// Return float between 0 and 1
// Pretty colors
float randf();

void regular_polygon_points(double radius, int num_verts);

#endif //GRAPHICSGROUPPROJECT_GLOBALS_H
