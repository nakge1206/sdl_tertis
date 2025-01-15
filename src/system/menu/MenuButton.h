#ifndef MENU_BUTTON_H
#define MENU_BUTTON_H

#include "../../definitions.h"
#include <string>

class MenuButton {
public:
    MenuButton() {}
    MenuButton(SDL_Renderer* renderer, const std::string& text, int x, int y, int width, int height, int fontSize);
    ~MenuButton();

    void render();
    bool isMouseOver(int mouseX, int mouseY) const;
    void setHighlight(bool highlight);
    void setOnClick(void (*onClick)());
    std::string getText() const { return text; } // 텍스트를 반환하는 함수 추가

private:
    SDL_Renderer* renderer;
    SDL_Rect rect;
    std::string text;
    bool highlight;
    void (*onClick)();
    int fontSize;

    SDL_Color defaultColor;
    SDL_Color highlightColor;
};

#endif