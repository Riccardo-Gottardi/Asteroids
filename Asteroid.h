//
// Created by riccardo on 23/02/24.
//

#ifndef ASTEROIDS_ASTEROID_H
#define ASTEROIDS_ASTEROID_H

#include "DataDefinition.h"

/*
 * MISSION: Represent an asteroid, it has a dimension, when you destroy an asteroid it spawn smaller dimension asteroid
 */
class Asteroid {
private:
    int dim;    // 3 possible
    int life;
    int r;
    int sides;
    float center[2];
    std::vector<float> edges;
    int* indices;
    float* dir;
    float v;
    void generateShape(std::uniform_real_distribution<double> dis, std::mt19937 gen);
    void generateDir(std::uniform_real_distribution<double> dis, std::mt19937 gen);
public:
    explicit Asteroid(int dim);
    void update(float delta_time);
    void draw(SDL_Renderer* ren);

    // Destroy the current asteroid and spawn the child
    void die();


};


#endif //ASTEROIDS_ASTEROID_H
