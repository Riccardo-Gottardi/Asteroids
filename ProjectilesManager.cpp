//
// Created by riccardo on 31/03/24.
//

#include "ProjectilesManager.h"

ProjectilesManager::ProjectilesManager() {
    this->firstFreePosition = 0;
    this->length = 5;
    this->pList = (Projectile**)calloc(this->length, sizeof(Projectile*));
}

void ProjectilesManager::nextFreePosition() {
    while(this->firstFreePosition < this->length) {
        if(this->pList[this->firstFreePosition] == nullptr) {
            break;
        }
        this->firstFreePosition += 1;
    }
}

void ProjectilesManager::printState() {
    std::cout << "Length: " << this->length << std::endl;
    std::cout << "FirstFreePosition: " << this->firstFreePosition << std::endl;
    std::cout << "PList: " << std::endl;
    for(int i = 0; i < this->length; ++i) {
        std::cout << i << " " << this->pList[i] << std::endl;
    }
    std::cout << std::endl << std::endl;
}

void ProjectilesManager::add(Projectile *p) {
    if(this->firstFreePosition >= this->length) {
        this->length *= 2;
        this->pList = (Projectile **) realloc(this->pList, this->length * sizeof(Projectile*));
        for(int i = this->firstFreePosition; i < this->length; ++i) {
            this->pList[i] = nullptr;
        }
    }
    this->pList[this->firstFreePosition] = p;
    this->nextFreePosition();
    // this->printState();
}

void ProjectilesManager::remove(Projectile *p) {

}

void ProjectilesManager::update(float delta_time) {
    for(int i = 0; i < this->length; ++i) {
        if(this->pList[i] != nullptr) {
            this->pList[i]->update(delta_time);
        }
    }
}

void ProjectilesManager::draw(SDL_Renderer *ren) {
    for(int i = 0; i < this->length; ++i) {
        if(this->pList[i] != nullptr) {
            this->pList[i]->draw(ren);
        }
    }
}