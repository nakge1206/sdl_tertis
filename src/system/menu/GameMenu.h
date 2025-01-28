#pragma once

#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <vector>
#include "../sdl/CreateButton.h"
#include "../sdl/SDL_font.h"
#include "../sdl/SDL_Input.h"

class GameMenu {
public:
    GameMenu();
    ~GameMenu();

    void initGameMenu(SDL_Renderer* rend, SDL_Window* window);
    void run();

    //키마 처리
    void UpClick();
    void DownClick();
    void EnterClick();
    void OnClick();

    bool isBack;

private:
    SDL_Renderer* rend;
    SDL_Window* window;

    //상태 고정하기 위함
    enum GAMEMENU {
        NOTHING,
        SINGLE40,
        SINGLE1M,
        SINGLEAI,
        MULTI
    };
    GAMEMENU gameMenuState;

    //메인메뉴 구현에 필요한 변수들
    std::vector<CreateButton> mainButtons;
    CreateButton back;
    SDL_font guide_40;
    SDL_font guide_1m;
    SDL_font guide_ai;
    SDL_font guide_multi;

    int mouseX, mouseY;

    void render();
    void handelEvent();
};