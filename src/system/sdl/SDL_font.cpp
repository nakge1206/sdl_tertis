#include "SDL_font.h"

SDL_font::SDL_font()
    : rend(nullptr), texture(nullptr), surface(nullptr){

    }

SDL_font::~SDL_font(){
    if (surface) {
        SDL_FreeSurface(surface);
        surface = nullptr;
    }
    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}

void SDL_font::initFont(SDL_Renderer* rend, const std::string& fontName, int fontSize){
    this->rend = rend;
    //폰트 경로 설정
    std::string fontNameFath = "src/assets/";
    fontNameFath = fontNameFath + fontName + ".ttf";

    font = TTF_OpenFont(fontNameFath.c_str(), fontSize);
    if(!font){
        std::cerr << "폰트열기 오류: " << SDL_GetError() << std::endl;
        throw std::runtime_error("TTF_OpenFont 실패: 폰트를 열 수 없습니다.");
    }
}

void SDL_font::textSetting(const std::string& text, SDL_Color textColor){
    createTexture(text, textColor);
    destRect.x = 50;
    destRect.y = 50;
    destRect.w = surface->w;
    destRect.h = surface->h;
}

void SDL_font::setPosition(float x, float y) {
    setPosition(x, y, surface->w, surface->h);
}

void SDL_font::setPosition(float x, float y, float w, float h){
    destRect.x = x;
    destRect.y = y;
    destRect.w = w;
    destRect.h = h;
}

void SDL_font::setPosition(SDL_Rect rect){
    destRect.x = rect.x;
    destRect.y = rect.y;
    destRect.w = rect.w;
    destRect.h = rect.h;
}

void SDL_font::setTextColor(const std::string& text, SDL_Color textColor){
    createTexture(text, textColor);
}

int SDL_font::getSurfaceInfo(char m){
    if(m == 'w') return surface->w;
    else if (m == 'h') return surface->h;
    else return 0;
}

void SDL_font::render(){
    SDL_RenderCopy(rend, texture, nullptr, &destRect);
}

void SDL_font::createTexture(const std::string& text, SDL_Color textColor){
    if (surface) {
        SDL_FreeSurface(surface);
        surface = nullptr;
    }
    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
    surface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    texture = SDL_CreateTextureFromSurface(rend, surface);
}