#ifndef MENU_CREATE_H
#define MENU_CREATE_H

#include "../../definitions.h"
#include <string>
#include <vector>
#include "MenuButton.h"
#include <functional>


class MenuCreate {
public:
    MenuCreate() : renderer(nullptr), window(nullptr) {}
    MenuCreate(SDL_Renderer* renderer, SDL_Window* window);
    ~MenuCreate();

    // 버튼 초기화
    void initButtons(const std::vector<std::string>& buttonTexts);
    // 버튼 렌더링
    void render();
    // 버튼 클릭 이벤트 처리
    void handleClick(int mouseX, int mouseY, void (*onClick)(const std::string&));
    // void updateMouseOver(int mouseX, int mouseY);

private:
    SDL_Renderer* renderer;
    SDL_Window* window;
    std::vector<MenuButton> buttons;
};

#endif