#pragma once

#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include "menu/MainMenu.h"
#include "sdl/SDL_Input.h"

class Window { //초기 창 열기
private:
    SDL_Window* window;
    SDL_Renderer* rend;
    bool isRunning;
    SDL_Input* input;

    //게임 상태 및 현재 상태
    enum MainState {
        MAIN,
        GAME,
        SETTINGS,
        QUIT
    };
    MainState currentState;
    bool isPause;

    MainMenu mainMenu;

    //게임 내 프레임 관련
    uint32_t frameStart;
    int frameTime;

    void HandleEvents();
    void Update();
    void Render();

public:
    Window(); //생성자
    ~Window(); //소멸자

    bool initSetting(const char* title, int width, int height);//SDL 초기설정
    void Run(); //실행
    void Shutdown(); //랜더러, 윈도우 삭제하고, SDL끝내기.
};
