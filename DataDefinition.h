#ifndef ASTEROIDS_DATADEFINITION_H
#define ASTEROIDS_DATADEFINITION_H

#include <iostream>
#include <cstdlib>
#include <random>
#include <cmath>
#include <vector>
#include <ctime>
#include <SDL2/SDL.h>

#define WIDTH 800
#define HEIGHT 800
#define PI 3.1415926f
#define INPUT_ACCELERATION 150.0f
#define MAX_VELOCITY 200.0f

struct mouse {
    int x;
    int y;
};
typedef struct mouse mouse;

struct spaceshipAction {
    bool up;
    bool down;
    bool left;
    bool right;
    bool shoot;
};
typedef struct spaceshipAction spaceshipAction;

#endif //ASTEROIDS_DATADEFINITION_H
