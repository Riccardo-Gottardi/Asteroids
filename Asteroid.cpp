//
// Created by riccardo on 23/02/24.
//

#include "Asteroid.h"

Asteroid::Asteroid(int dim) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0.0, 1.0);
    this->dim = dim;
    if (dim == 1)
        this->life = 1;
    else
        this->life = dim - 1 * 3;
    this->r = 25 * dim;
    this->sides = 6 * dim;
    this->center[0] = 100.0f;
    this->center[1] = 100.0f;
    this->indices = (int*)malloc(sizeof(int) * 3 * this->sides);
    this->generateShape(dis, gen);
    this->generateDir(dis, gen);
    this->v = 60.0f + (float)dis(gen) * 50.0f;
}

void Asteroid::generateShape(std::uniform_real_distribution<double> dis, std::mt19937 gen) {
    float angle = 0.0f;
    float vec;
    for(int i = 0; i < this->sides; ++i) {
        vec = ((float)this->r/2) * (float)dis(gen) + (float)this->r/2;
        this->edges.push_back(vec * cos(angle));
        this->edges.push_back(vec * sin(angle));
        angle +=  (2 * PI) / (float)this->sides;
    }
    for(int i = 0; i < this->sides - 1 ; ++i) {
        this->indices[3*i] = 0;
        this->indices[3*i + 1] = i + 1;
        this->indices[3*i + 2] = i + 2;
    }
    this->indices[3*(this->sides - 1)] = 0;
    this->indices[3*(this->sides - 1) + 1] = this->sides;
    this->indices[3*(this->sides -1 ) + 2] = 1;
}

void Asteroid::generateDir(std::uniform_real_distribution<double> dis, std::mt19937 gen) {
    float l = (float)sqrt(pow(((float)WIDTH/2 - this->center[0]), 2) + pow(((float)HEIGHT/2 - this->center[1]), 2));
    float rand_angle = (float)(dis(gen)) * PI/3 - PI/6;
    float angle = asin(((float)WIDTH/2 - this->center[1])/l) + rand_angle;
    this->dir[0] = cos(angle);
    this->dir[1] = sin(angle);
}

void Asteroid::update(float delta_time) {
    this->center[0] += this->dir[0] * this->v * delta_time;
    this->center[1] += this->dir[1] * this->v * delta_time;
}

void Asteroid::draw(SDL_Renderer* ren) {
    /*
    SDL_Vertex vertices[this->sides + 1];
    vertices[0] = {{this->center[0], this->center[1]}, {200, 200, 200, 1}};
    for(int i = 0; i < this->sides; ++i) {
        vertices[i + 1] = {{this->center[0] + this->edges.at(2*i), this->center[1] + this->edges.at(2*i + 1)}, {200, 200, 200, 1}};
    }
    SDL_RenderGeometry(ren, nullptr, vertices, this->sides + 1, this->indices, 3 * this->sides);
    */

    SDL_FPoint points[this->sides + 1];
    for(int i = 0; i < this->sides; ++i) {
        points[i] = {this->center[0] + this->edges.at(2*i), this->center[1] + this->edges.at(2*i + 1)};
    }
    points[this->sides] = {this->center[0] + this->edges.at(0), this->center[1] + this->edges.at(1)};
    SDL_SetRenderDrawColor(ren, 200, 200, 200, 255);
    SDL_RenderDrawLinesF(ren, points, this->sides + 1);

}