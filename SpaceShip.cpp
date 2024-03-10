//
// Created by riccardo on 10/02/24.
//

#include "SpaceShip.h"

SpaceShip::SpaceShip() {
    this->life = 3;
    this->x = 400;
    this->y = 400;
    this->vx = 0;
    this->vy = 0;
    this->ax = 0;
    this->ay = 0;
    this->angle = 0;
    this->dir = 0;
    this->action = {
            .up = false,
            .down = false,
            .left = false,
            .right = false,
            .shoot = false
    };
}

void SpaceShip::setUp(bool state) {
    this->action.up = state;
}

void SpaceShip::setDown(bool state) {
    this->action.down = state;
}

void SpaceShip::setLeft(bool state) {
    this->action.left = state;
}

void SpaceShip::setRight(bool state) {
    this->action.right = state;
}

void SpaceShip::setShoot(bool state) {
    this->action.shoot = state;
}

void SpaceShip::update(mouse mouse, float delta_time) {
    this->ax = 0;
    this->ay = 0;

    if(this->action.up) {
        if (this->vy > 0) {
            this->ay = -2 * INPUT_ACCELERATION;
        } else {
            this->ay = -INPUT_ACCELERATION;
        }
    }
    if(this->action.down) {
        if (this->vy < 0) {
            this->ay = 2 * INPUT_ACCELERATION;
        } else {
            this->ay = INPUT_ACCELERATION;
        }
    }
    if(this->action.left) {
        if (this->vx > 0) {
            this->ax = -2 * INPUT_ACCELERATION;
        } else {
            this->ax = -INPUT_ACCELERATION;
        }
    }
    if(this->action.right) {
        if (this->vx < 0) {
            this->ax = 2 * INPUT_ACCELERATION;
        } else {
            this->ax = INPUT_ACCELERATION;
        }
    }

    this->vx += this->ax * delta_time;
    this->vy += this->ay * delta_time;
    this->x += 0.5f * this->ax * delta_time * delta_time + this->vx * delta_time;
    this->y += 0.5f * this->ay * delta_time * delta_time + this->vy * delta_time;

    if(this->x < 0) {
        this->x = 0;
        this->vx = 0.0f;
    }
    if(this->x > (float)WIDTH) {
        this->x = (float)WIDTH;
        this->vx = 0.0f;
    }
    if(this->y < 0) {
        this->y = 0;
        this->vy = 0.0f;
    }
    if(this->y > (float)HEIGHT) {
        this->y = (float)HEIGHT;
        this->vy = 0.0f;
    }

    float dx = (float)mouse.x - this->x;
    float dy = -( (float)mouse.y - this->y );
    float i = sqrt(dx*dx + dy*dy);
    this->angle = acos(dx/i);
    this->dir = (int)(dy / abs(dy));

    if(this->vx > MAX_VELOCITY) this->vx = MAX_VELOCITY;
    if(this->vx < -MAX_VELOCITY) this->vx = -MAX_VELOCITY;
    if(this->vy > MAX_VELOCITY) this->vy = MAX_VELOCITY;
    if(this->vy < -MAX_VELOCITY) this->vy = -MAX_VELOCITY;

    this->setUp(false);
    this->setDown(false);
    this->setLeft(false);
    this->setRight(false);
}

void SpaceShip::draw(SDL_Renderer* ren) {
    SDL_Vertex vertices[4] = {
            {{this->x + 5*cos(-PI - (float)this->dir*this->angle), this->y + 5*sin(-PI - (float)this->dir*this->angle)}, {255, 255, 255, 255}},
            {{this->x + 15*cos(-5*PI/4 - (float)this->dir*this->angle), this->y + 15*sin(-5*PI/4 - (float)this->dir*this->angle)}, {255, 255, 255, 255}},
            {{this->x + 15*cos(-(float)this->dir*this->angle), this->y + 15*sin(-(float)this->dir*this->angle)}, {255, 255, 255, 255}},
            {{this->x + 15*cos(-3*PI/4 - (float)this->dir*this->angle), this->y + 15*sin(-3*PI/4 - (float)this->dir*this->angle)}, {255, 255, 255, 255}}
    };

    SDL_RenderGeometry(ren, nullptr, vertices, 4, this->indices, 6);
}