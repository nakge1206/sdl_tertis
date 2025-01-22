#pragma once

#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <vector>
#include "../sdl/CreateButton.h"
#include "../sdl/SDL_font.h"
#include "../sdl/SDL_Input.h"

class SettingMenu {
public:
    SettingMenu() {};
    SettingMenu(SDL_Renderer* rend, SDL_Window* window);
    ~SettingMenu();

    void initSetting(); //세팅화면 미리 정해두기
    void render(); //메인메뉴 렌더링

private:
    SDL_Renderer* rend;
    SDL_Window* window;
    SDL_Rect pausefill;

    //메인메뉴 구현에 필요한 변수들
    std::vector<CreateButton> settingButtons;
};