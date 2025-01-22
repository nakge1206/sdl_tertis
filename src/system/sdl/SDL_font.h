#pragma once
#include "../../definitions.h"
#include <SDL2/SDL.h>
#include <string>

class SDL_font {
public:
    SDL_font();
    ~SDL_font();

    //글자 관련 기본 설정
    void initFont(SDL_Renderer* rend, const std::string& fontName,int fontSize);
    void textSetting(const std::string& text, SDL_Color textColor);
    
    //글자 위치 설정
    void setPosition(float x, float y);
    void setPosition(float x, float y, float w, float h);
    void setPosition(SDL_Rect rect);

    //글자 색상 변경
    void setTextColor(const std::string& text, SDL_Color textColor);
    
    //글자 크기 받는 함수
    int getSurfaceInfo(char m);
    
    //렌더
    void render();

private:
    SDL_Renderer* rend;
    int fontSize;
    SDL_Rect destRect;
    TTF_Font* font;
    SDL_Texture* texture;
    SDL_Surface* surface;

    void createTexture(const std::string& text, SDL_Color textColor);   
};