#ifndef GRAPHICSGROUPPROJECT_GLOBALS_H
#define GRAPHICSGROUPPROJECT_GLOBALS_H

#include <cmath>
#include <random>

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

#endif //GRAPHICSGROUPPROJECT_GLOBALS_H
