#pragma once

#include "../../definitions.h"
#include "../sdl/SDL_font.h"
#include <string>

class CreateButton {
public:
    CreateButton();
    ~CreateButton();

    //버튼 기본 정보 입력
    void initButton(SDL_Renderer* rend, const std::string& text, int x, int y, int width, int height, int fontSize, const std::string& fontName = "font");

    //버튼 위치 설정
    void setPosition(int x, int y);
    void setPosition(int x, int y, int w, int h);
    void setPosition(SDL_Rect destRect);

    //버튼 및 글자 색상 바꾸기
    void setDefaultColor(SDL_Color basic);
    void setHighlightColor(SDL_Color Highlight);
    void setTextColor(const std::string& text, SDL_Color textColor);

    //마우스 관련 처리
    bool isMouseOver(int mouseX, int mouseY) const;
    void setHighlight(bool highlight);
    void setprint();

    //렌더
    void render();


private:
    SDL_Renderer* rend;
    SDL_Rect rect;
    std::string text;
    bool highlight;
    SDL_font buttonText;

    SDL_Color defaultColor;
    SDL_Color highlightColor;

    SDL_Rect cal_textRect(); //버튼 정보를 가지고, 버튼 중앙의 위치를 반환시키는 함수
};