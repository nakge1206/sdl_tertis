#include "Particle.h"
#include <cstdlib>

bool isDeadCheck(const Particle& p) {
    return p.isDead();
}

Particle::Particle(int x, int y, SDL_Renderer* renderer)
    : x(x), y(y), renderer(renderer), life(50) {
    color.r=rand()%256; color.g=rand()%256; color.b=rand()%256; color.a=255;
}

void Particle::update() {
    --life;
    x += rand() % 7 - 3;
    y += rand() % 7 - 3;
}

void Particle::render() {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect = {x, y, 4, 4};
    SDL_RenderFillRect(renderer, &rect);
}

bool Particle::isDead() const {
    return life <= 0;
}

ParticleSystem::ParticleSystem(SDL_Renderer* renderer) : renderer(renderer) {}

void ParticleSystem::createExplosion(int x, int y) {
    for (int i = 0; i < 50; ++i) {
        particles.emplace_back(x, y, renderer);
    }
}

void ParticleSystem::update() {
    particles.erase(
    std::remove_if(particles.begin(), particles.end(), isDeadCheck),
    particles.end()
    );  

    for (size_t i = 0; i < particles.size(); ++i) {
        Particle& p = particles[i];
        p.update();
    }

}

void ParticleSystem::render() {
    for (size_t i = 0; i < particles.size(); ++i) {
        Particle& p = particles[i];
        p.update();
    }
}