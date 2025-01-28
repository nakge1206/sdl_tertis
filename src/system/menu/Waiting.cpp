#include "Waiting.h"

Waiting::Waiting() : rend(nullptr), window(nullptr){
}

Waiting::~Waiting(){

}

void Waiting::init(SDL_Renderer* rend, SDL_Window* window){
    this->rend = rend; this->window = window;

    int fontSize = 50;
    waiting.initFont(rend, "font", fontSize);
    SDL_Color textColor = {255, 255, 255, 255}; //흰색
    waiting.textSetting("not complete. back is \"B\"", textColor);
    int titleX = 0; //960 / 2;
    int titleY = 220;
    waiting.setPosition(titleX, titleY);
}

void Waiting::render() {
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
    SDL_RenderClear(rend);

    waiting.render();
}