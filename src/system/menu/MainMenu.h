#pragma once


#include <vector>

#include "../sdl/CreateButton.h"
#include "../sdl/SDL_Input.h"

class MainMenu {
public:
    MainMenu();
    ~MainMenu();

    void initMain(SDL_Renderer* rend, SDL_Window* window); //메인메뉴 미리 정해두기
    void run();

    //키마 처리
    void UpClick();
    void DownClick();
    void EnterClick();
    void OnClick();

    bool isQuit;
    bool mainStart;
    bool mainSetting;

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

    int mouseX, mouseY;

    void render();
    void handelEvent();
};