#pragma once

#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <vector>
#include "../sdl/CreateButton.h"
#include "../sdl/SDL_font.h"
#include "../sdl/SDL_Input.h"

class MainMenu {
public:
    MainMenu();
    ~MainMenu();

    void initMain(SDL_Renderer* rend, SDL_Window* window); //메인메뉴 미리 정해두기
    void render(); //메인메뉴 렌더링

private:
    SDL_Renderer* rend;
    SDL_Window* window;

    //상태 고정하기 위함
    enum MAINMENUSTATE {
        NOTHING,
        MAIN_START,
        MAIN_SETTING,
        MAIN_QUIT
    };
    MAINMENUSTATE mainState;

    //메인메뉴 구현에 필요한 변수들
    std::vector<CreateButton> mainButtons;
    SDL_font title;
    SDL_font madeBy;


    //디버그용 변수
    bool testa;
};