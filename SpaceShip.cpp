//
// Created by riccardo on 10/02/24.
//

#include "SpaceShip.h"
#include <cstdlib>

SpaceShip::SpaceShip() {
    this->life = 3;
    this->x = (float)WIDTH / 2;
    this->y = (float)HEIGHT / 2;
    this->vx = 0;
    this->vy = 0;
    this->ax = 0;
    this->ay = 0;
    this->angle = 0;
    this->reflect = 0;
    this->life = 3;
    this->action = {
            .up = false,
            .down = false,
            .left = false,
            .right = false,
            .shoot = false
    };
    this->projectilesManager = new ProjectilesManager();
    this->projectileVelAmplifier = 1;
    this->damage = 1;
    this->shootAgain = 0.75;
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
    if(this->action.shoot) {
        if(this->shootAgain >= 0.75) {
            this->shoot();
        }
    }
    if(this->shootAgain < 0.75) {
        this->shootAgain += delta_time;
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
    this->reflect = (int)(dy / abs(dy));

    if(this->vx > MAX_VELOCITY) this->vx = MAX_VELOCITY;
    if(this->vx < -MAX_VELOCITY) this->vx = -MAX_VELOCITY;
    if(this->vy > MAX_VELOCITY) this->vy = MAX_VELOCITY;
    if(this->vy < -MAX_VELOCITY) this->vy = -MAX_VELOCITY;

    this->setUp(false);
    this->setDown(false);
    this->setLeft(false);
    this->setRight(false);
    this->setShoot(false);

    this->projectilesManager->update(delta_time);
}

void SpaceShip::draw(SDL_Renderer* ren) {
    SDL_Vertex vertices[4] = {
            {{this->x + 5*cos(-PI - (float)this->reflect*this->angle), this->y + 5*sin(-PI - (float)this->reflect*this->angle)}, {255, 255, 255, 255}},
            {{this->x + 15*cos(-5*PI/4 - (float)this->reflect*this->angle), this->y + 15*sin(-5*PI/4 - (float)this->reflect*this->angle)}, {255, 255, 255, 255}},
            {{this->x + 15*cos(-(float)this->reflect*this->angle), this->y + 15*sin(-(float)this->reflect*this->angle)}, {255, 255, 255, 255}},
            {{this->x + 15*cos(-3*PI/4 - (float)this->reflect*this->angle), this->y + 15*sin(-3*PI/4 - (float)this->reflect*this->angle)}, {255, 255, 255, 255}}
    };

    SDL_RenderGeometry(ren, nullptr, vertices, 4, this->indices, 6);

    this->projectilesManager->draw(ren);
}

void SpaceShip::shoot() {
    this->shootAgain = 0;
    auto *p = new Projectile(this->x, this->y, 10.0f, this->angle, this->reflect, BASE_PROJECTILE_VELOCITY * this->projectileVelAmplifier, this->vx, this->vy, this->damage, {255, 100, 100, 255});
    this->projectilesManager->add(p);
}