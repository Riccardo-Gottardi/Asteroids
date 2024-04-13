//
// Created by riccardo on 23/02/24.
//

#ifndef ASTEROIDS_ASTEROID_H
#define ASTEROIDS_ASTEROID_H

#include "DataDefinition.h"

/*
 * MISSION: Represent an asteroid, it has a dimension, when you destroy an asteroid it spawns smaller dimension asteroid
 */
class Asteroid {
private:
    int r;
    float center[2];
    int dim;                    // categorize the type of asteroids based on the dimension
    int life;
    int sides;                  // number of sides of the polygon
    std::vector<float> edges;   // collection of edges coordinate of the polygon
    int* indices;               // collection of indices of the triangles used to fill the polygon
    float dir[2];               // direction vector
    float v;                    // velocity
    void generateShape(std::uniform_real_distribution<double> dis, std::mt19937 gen);
    void generateDir(std::uniform_real_distribution<double> dis, std::mt19937 gen);
public:
    explicit Asteroid(int dim);
    void update(float delta_time);
    void draw(SDL_Renderer* ren);
    void die();                 // Destroy the current asteroid and spawn the child


};


#endif //ASTEROIDS_ASTEROID_H
