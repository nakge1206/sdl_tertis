#pragma once

#include "../../definitions.h"
#include "../sdl/SDL_font.h"
#include <string>

class MenuButton {
public:
    MenuButton() {}
    MenuButton(SDL_Renderer* rend, const std::string& text, int x, int y, int width, int height, int fontSize);
    ~MenuButton();

    void render();

    void setPosition(int x, int y);
    void setPosition(int x, int y, int w, int h, int fontSize);
    void setPosition(SDL_Rect destRect);

    bool isMouseOver(int mouseX, int mouseY) const;
    void setHighlight(bool highlight);
    void setOnClick(void (*onClick)());
    void setprint();
    std::string getText() const { return text; } // 텍스트를 반환하는 함수 추가

private:
    SDL_Renderer* rend;
    SDL_Rect rect;
    std::string text;
    bool highlight;
    void (*onClick)();
    int fontSize;
    SDL_font buttonText;

    SDL_Color defaultColor;
    SDL_Color highlightColor;
};