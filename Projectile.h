//
// Created by riccardo on 23/02/24.
//

#ifndef ASTEROIDS_PROJECTILE_H
#define ASTEROIDS_PROJECTILE_H
#include "DataDefinition.h"

class Projectile {
private:
    float x;
    float y;
    float width;
    float v;
    float spaceshipVX;
    float spaceshipVY;
    float angle;
    int reflect;
    float damage;
    SDL_Color color;
    int indices[6] = {
            0, 1, 2,
            2, 3, 1
    };

public:
    Projectile(float x, float y, float width, float angle, int reflect, float v, float spaceshipVX, float spaceshipVY, float damage, SDL_Color color);
    void update(float delta_time);
    void draw(SDL_Renderer* ren);
    bool isOut();       // check if the projectile is out of the screen bound -> so it needs to be deleted
};


#endif //ASTEROIDS_PROJECTILE_H
