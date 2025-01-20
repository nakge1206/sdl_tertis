#pragma once

#include "../definitions.h"
#include "menu/MenuButton.h"
#include "menu/Particle.h"
#include "menu/TotalMenu.h"
#include "sdl/SDL_Input.h"

class Window { //초기 창 열기
private:
    SDL_Window* window;
    SDL_Renderer* rend;
    bool isRunning;
    bool isWindowResized;

    //게임 상태 및 현재 상태
    enum GameState {
        MAIN_MENU,
        GAME,
        SETTINGS,
        QUIT
    };
    GameState currentState;

    TotalMenu menus;

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
