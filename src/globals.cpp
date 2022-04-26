#include "globals.h"

#include <ctime>
#include <random>

void initrand()
{
    srand(time(nullptr)); // Yes, time is bad as a seed. This is for colors only.
}

float randf()
{
    return (float) std::rand() / (float) RAND_MAX;
}