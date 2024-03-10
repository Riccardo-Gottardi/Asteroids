#include "DataDefinition.h"
#include "SpaceShip.h"
#include "Asteroid.h"

void EventManager(bool* quit, SpaceShip& spaceship, mouse* mouse);
void UpdateDeltaTime(float* delta_time, unsigned long* current_ticks, unsigned long* last_ticks);

int main() {
    mouse mouse = {
        .x = 0,
        .y = 0
    };

    SpaceShip spaceship;
    Asteroid asteroid(3);

    if(SDL_Init(SDL_INIT_EVERYTHING) == -1) {
        perror("SDL_Init()");
        exit(EXIT_FAILURE);
    }

    SDL_Window* win = SDL_CreateWindow("Asteroids", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);
    if(!win) {
        perror("SLD_CreateWindow()");
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if(!ren) {
        perror("SDL_CreateRenderer()");
        SDL_DestroyWindow(win);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    // TODO : load logo

    float delta_time = 0;
    unsigned long current_ticks = 0, last_ticks = 0;
    bool quit = false;
    while(!quit) {

        UpdateDeltaTime(&delta_time, &current_ticks, &last_ticks);

        //Event handling
        EventManager(&quit, spaceship, &mouse);

        spaceship.update(mouse, delta_time);
        asteroid.update(delta_time);

        SDL_SetRenderDrawColor(ren, 10, 10, 30, 255);
        SDL_RenderClear(ren);

        spaceship.draw(ren);
        asteroid.draw(ren);

        SDL_RenderPresent(ren);

        // UpdateSpaceship(&spaceship);

        SDL_Delay(1000/60);
    }
 
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}


void EventManager(bool* quit, SpaceShip& spaceship, mouse* mouse) {
    SDL_Event e;
    const unsigned char* keyboardState = SDL_GetKeyboardState(nullptr);
    long click = SDL_GetMouseState(&(mouse->x), &(mouse->y));

    while(SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT:
                *quit = true;
                break;
            default:
                break;
        }
    }
    if(keyboardState[SDL_SCANCODE_ESCAPE]) *quit = true;
    if(keyboardState[SDL_SCANCODE_W] || keyboardState[SDL_SCANCODE_UP]) spaceship.setUp(true);
    if(keyboardState[SDL_SCANCODE_S] || keyboardState[SDL_SCANCODE_DOWN]) spaceship.setDown(true);
    if(keyboardState[SDL_SCANCODE_A] || keyboardState[SDL_SCANCODE_LEFT]) spaceship.setLeft(true);
    if(keyboardState[SDL_SCANCODE_D] || keyboardState[SDL_SCANCODE_RIGHT]) spaceship.setRight(true);
    if(keyboardState[SDL_SCANCODE_SPACE] || click == 1) spaceship.setShoot(true);
}

void UpdateDeltaTime(float* delta_time, unsigned long* current_ticks, unsigned long* last_ticks) {
    *current_ticks = SDL_GetTicks64();
    *delta_time = (float)(*current_ticks - *last_ticks) / 1000.0f;
    *last_ticks = *current_ticks;
}