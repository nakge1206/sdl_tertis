#pragma once

#include "../sdl/SDL_font.h"
#include <SDL2/SDL.h>

class Waiting {
public:
    Waiting();
    ~Waiting();

    void init(SDL_Renderer* rend, SDL_Window* window);
    void render();


private:
    SDL_Renderer* rend;
    SDL_Window* window;

    SDL_font waiting;
};