#pragma once

#include "../../definitions.h"
#include <vector>

class Particle {
public:
    Particle(int x, int y, SDL_Renderer* renderer);
    void update();
    void render();
    bool isDead() const;

private:
    int x, y;
    int life;
    SDL_Renderer* renderer;
    SDL_Color color;
};

class ParticleSystem {
public:
    ParticleSystem(SDL_Renderer* renderer);
    void createExplosion(int x, int y);
    void update();
    void render();

private:
    SDL_Renderer* renderer;
    std::vector<Particle> particles;
};
