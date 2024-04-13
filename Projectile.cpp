//
// Created by riccardo on 23/02/24.
//

#include "Projectile.h"

Projectile::Projectile(float x, float y, float width, float angle, int reflect, float v, float spaceshipVX, float spaceshipVY, float damage, SDL_Color color) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->angle = angle;
    this->reflect = reflect;
    this->v = v;
    this->spaceshipVX = spaceshipVX;
    this->spaceshipVY = spaceshipVY;
    this->damage = damage;
    this->color = color;
}

void Projectile::update(float delta_time) {
    this->x += (cos((float)this->reflect * this->angle) * this->v + this->spaceshipVX) * delta_time;
    this->y += (-1 * sin((float)this->reflect * this->angle) * this->v + this->spaceshipVY) * delta_time;
}

void Projectile::draw(SDL_Renderer *ren) {
    SDL_Vertex vertices[4] = {
            {{this->x - this->width/2, this->y - this->width/2}, this->color},
            {{this->x + this->width/2, this->y - this->width/2}, this->color},
            {{this->x - this->width/2, this->y + this->width/2}, this->color},
            {{this->x + this->width/2, this->y + this->width/2}, this->color}
    };

    SDL_RenderGeometry(ren, nullptr, vertices, sizeof(vertices)/sizeof(SDL_Vertex), this->indices, sizeof(this->indices)/sizeof(int));
}

bool Projectile::isOut() {
    if(this->x + this->width/2 < 0 || this->x - this->width/2 > WIDTH || this->y + this->width/2 > 0 || this->y - this->width/2 > HEIGHT) {
        return true;
    } else {
        return false;
    }
}