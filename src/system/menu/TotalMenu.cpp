#include "TotalMenu.h"
#include <SDL_ttf.h>
#include <iostream>

TotalMenu::TotalMenu(SDL_Renderer* rend, SDL_Window* window)
    : rend(rend), window(window), currentMenu(MAIN) {}

TotalMenu::~TotalMenu() {
}

//메인메뉴 화면 미리 정해놓기
void TotalMenu::initMainMenu() {
    mainMenuButtons.clear();
    /* 960x540 기준 버튼 크기들
    buttonWidth = 960 * 0.16 = 153
    buttonHeight = 540 * 0.1 = 54
    buttonSpacing = 540 * 0.05 = 27
    totalHeight = (buttonHeight * 3) + (buttonSpacing * (2))
                = (54 * 3) + (27 * 2) =  162 + 54 = 216
    term = 54 + 27 = 71
    */

    //버튼 생성
    int buttonWidth = 960 * 0.2;
    int buttonHeight = 540 * 0.13;
    int buttonSpacing = 540 * 0.05;

    int startX = (960 - buttonWidth) / 2;
    int totalHeight = (buttonHeight * 3) + (buttonSpacing * (2));
    int startY = (540 - totalHeight) / 2 + (buttonHeight*0.5);
    int term = buttonHeight + buttonSpacing;

    int fontSize = 25;
    mainMenuButtons.emplace_back(rend, "Start_Game", startX, startY, buttonWidth, buttonHeight, fontSize);
    mainMenuButtons.emplace_back(rend, "Setting", startX, startY + term, buttonWidth, buttonHeight, fontSize);
    mainMenuButtons.emplace_back(rend, "Quit", startX, startY + term + term, buttonWidth, buttonHeight, fontSize);

    //게임 이름
    fontSize = 60;
    title.initFont(rend, "font", fontSize);
    SDL_Color textColor = {255, 255, 255, 255}; //흰색
    title.textSetting("Naktris", textColor);
    int titleWidth = title.getSurfaceInfo('w');
    int titleHeight = title.getSurfaceInfo('h');
    int titleX = (960 - titleWidth) / 2;
    int titleY = ((540 - totalHeight) / 2) - (titleHeight);
    title.setPosition(titleX, titleY);

    //Made by
    fontSize = 15;
    madeBy.initFont(rend, "font", fontSize);
    madeBy.textSetting("mady by nakge_hurt", textColor);
    int madeWidth = madeBy.getSurfaceInfo('w');
    int madeHeight = madeBy.getSurfaceInfo('h');
    int madeX = 960 - madeWidth - 10;
    int madeY = 540 - (madeHeight * 2);
    madeBy.setPosition(madeX, madeY);
}


void TotalMenu::renderMainMenu() {
    //배경을 검은색으로 초기화
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
    SDL_RenderClear(rend);

    for(size_t i = 0; i < 3; ++i){
        mainMenuButtons[i].render();
    }
    title.render();
    madeBy.render();
}

// void TotalMenu::renderPauseMenu() {
//     // 어두운 배경
//     SDL_SetRenderDrawColor(rend, 0, 0, 0, pauseBackgroundAlpha);
//     SDL_RenderFillRect(rend, nullptr);

//     // for (auto& button : pauseMenuButtons) {
//     //     button.render();
//     // }
// }

// void TotalMenu::renderSettingMenu() {
//     // 배경
//     SDL_SetRenderDrawColor(rend, 50, 50, 50, 255);
//     SDL_RenderClear(rend);

//     // for (auto& button : settingMenuButtons) {
//     //     button.render();
//     // }
// }

void TotalMenu::render() {
    int mouseX, mouseY;
    uint32_t mouseState = SDL_GetMouseState(&mouseX, &mouseY);
    switch (currentMenu) {
        case MAIN:
            renderMainMenu();
            for(size_t i=0; i<3; ++i){
                bool isMouse = mainMenuButtons[i].isMouseOver(mouseX, mouseY);
                //마우스가 위에 올라가면 하이라이트 표시
                mainMenuButtons[i].setHighlight(isMouse);
                //버튼 클릭시.
                if(mouseState && SDL_BUTTON(SDL_BUTTON_LEFT)&&isMouse){
                    mainMenuButtons[i].setprint();
                }
            }
            break;
        case PAUSE:
            //renderPauseMenu();
            break;
        case SETTING:
            //renderSettingMenu();
            break;
    }
}

void TotalMenu::setMenu(MenuType menu) {
    currentMenu = menu;
}

TotalMenu::MenuType TotalMenu::callType(int num){
    switch (num){
    case 0:
        return MAIN;
    case 1:
        return PAUSE;
    case 2:
        return SETTING;
    default:
        return MAIN;
        break;
    }
}


// void TotalMenu::initPauseMenu() {
//     pauseMenuButtons.clear();

//     int windowWidth, windowHeight;
//     SDL_GetWindowSize(window, &windowWidth, &windowHeight);

//     const int buttonWidth = windowWidth / 4;
//     const int buttonHeight = windowHeight / 10;
//     const int buttonSpacing = windowHeight / 20;

//     int startY = (windowHeight - (3 * buttonHeight + 2 * buttonSpacing)) / 2;

//     pauseMenuButtons.emplace_back(rend, "Continue", (windowWidth - buttonWidth) / 2, startY, buttonWidth, buttonHeight);
//     pauseMenuButtons.emplace_back(rend, "Settings", (windowWidth - buttonWidth) / 2, startY + buttonHeight + buttonSpacing, buttonWidth, buttonHeight);
//     pauseMenuButtons.emplace_back(rend, "Exit Game", (windowWidth - buttonWidth) / 2, startY + 2 * (buttonHeight + buttonSpacing), buttonWidth, buttonHeight);
// }

// void TotalMenu::initSettingMenu() {
//     settingMenuButtons.clear();

//     int windowWidth, windowHeight;
//     SDL_GetWindowSize(window, &windowWidth, &windowHeight);

//     const int labelWidth = windowWidth / 3;
//     const int buttonWidth = windowWidth / 6;
//     const int buttonHeight = windowHeight / 10;
//     const int buttonSpacing = windowHeight / 20;

//     int startY = (windowHeight - (3 * buttonHeight + 2 * buttonSpacing)) / 2;

//     settingMenuButtons.emplace_back(rend, "Toggle Option 1", labelWidth + buttonWidth, startY, buttonWidth, buttonHeight);
//     settingMenuButtons.emplace_back(rend, "Toggle Option 2", labelWidth + buttonWidth, startY + buttonHeight + buttonSpacing, buttonWidth, buttonHeight);
//     settingMenuButtons.emplace_back(rend, "Toggle Option 3", labelWidth + buttonWidth, startY + 2 * (buttonHeight + buttonSpacing), buttonWidth, buttonHeight);
// }