#pragma once
#include "../../definitions.h"
#include <string>

class SDL_font {
public:
    SDL_font();
    ~SDL_font();

    void initFont(SDL_Renderer* rend, const std::string& fontName,int fontSize);
    void textSetting(const std::string& text, SDL_Color textColor);
    void setPosition(float x, float y);
    void setPosition(float x, float y, float w, float h);
    void setPosition(SDL_Rect rect);
    int getSurfaceInfo(char m);
    TTF_Font* getFont();
    void render();

private:
    SDL_Renderer* rend;
    int fontSize;
    std::string fontName;
    TTF_Font* font;
    SDL_Rect destRect;
    SDL_Texture* texture;
    SDL_Surface* surface;
        
};