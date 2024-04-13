//
// Created by riccardo on 31/03/24.
//

#ifndef ASTEROIDS_PROJECTILESMANAGER_H
#define ASTEROIDS_PROJECTILESMANAGER_H

#include "Projectile.h"

class ProjectilesManager {
private:
    int firstFreePosition;
    int length;
    Projectile** pList;
    void nextFreePosition();
    void printState();

public:
    explicit ProjectilesManager();
    void add(Projectile *p);
    void remove(Projectile* p);
    void update(float delta_time);
    void draw(SDL_Renderer* ren);
};


#endif //ASTEROIDS_PROJECTILESMANAGER_H
