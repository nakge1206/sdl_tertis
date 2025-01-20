#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include "MenuButton.h"
#include "../sdl/SDL_font.h"
#include "../sdl/SDL_Input.h"

//todo.
//main메뉴 잘 뜨고, 마우스 위치 및 클릭 확인

class TotalMenu {
private:
    SDL_Renderer* rend;
    SDL_Window* window;

    // 각 메뉴의 버튼 리스트

    //메인메뉴 구현에 필요한 변수들
    std::vector<MenuButton> mainMenuButtons;
    SDL_font title;
    SDL_font madeBy;
    float WidthRatio;
    float HeightRatio;
    float SpacingRatio;

    //std::vector<MenuButton> pauseMenuButtons;
    //std::vector<MenuButton> settingMenuButtons;
    
    // 현재 메뉴 상태
    enum MenuType {
        MAIN,
        PAUSE,
        SETTING };
    MenuType currentMenu;

    //이거도 나중에 수정
    // 배경 투명도 (일시 정지 화면용)
    //int pauseBackgroundAlpha;

    void renderMainMenu();
    //void renderPauseMenu();
    //void renderSettingMenu();

public:
    TotalMenu() {};
    TotalMenu(SDL_Renderer* rend, SDL_Window* window);
    ~TotalMenu();

    //각 메뉴 초기화 메서드
    void initMainMenu();
    //void initPauseMenu();
    //void initSettingMenu();

    MenuType callType(int num);

    // 메뉴 렌더링
    void render();

    // 메뉴 변경
    void setMenu(MenuType menu);
};