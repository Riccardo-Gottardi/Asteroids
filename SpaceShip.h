//
// Created by riccardo on 10/02/24.
//

#ifndef ASTEROIDS_SPACESHIP_H
#define ASTEROIDS_SPACESHIP_H

#include "DataDefinition.h"

class SpaceShip {
private:
    int life;
    float x;
    float y;
    float vx;
    float vy;
    float ax;
    float ay;
    float angle;
    int dir;
    int indices[6] = {
            0, 1, 2,
            0, 3, 2
    };
    spaceshipAction action;
public:
    SpaceShip();
    void setUp(bool state);
    void setDown(bool state);
    void setLeft(bool state);
    void setRight(bool state);
    void setShoot(bool state);
    void update(mouse mouse, float delta_time);
    void draw(SDL_Renderer* ren);
    void die();
};

#endif //ASTEROIDS_SPACESHIP_H
