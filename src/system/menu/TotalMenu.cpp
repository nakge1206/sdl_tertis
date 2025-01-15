#include "TotalMenu.h"
#include <SDL_ttf.h>
#include <iostream>

TotalMenu::TotalMenu(SDL_Renderer* rend, SDL_Window* window)
    : rend(rend), window(window), currentMenu(MAIN){}

TotalMenu::~TotalMenu() {}

//이건 메뉴 버튼 초기화 하는거임.
void TotalMenu::initMainMenu() {
    mainMenuButtons.clear();
    //main의 기본설정인 1280x760 기준으로 초기세팅만 해두었음.
    mainMenuButtons.emplace_back(rend, "Start_Game", 484, 288, 320, 96, 48);
    mainMenuButtons.emplace_back(rend, "Setting", 484, 432, 320, 96, 48);
    mainMenuButtons.emplace_back(rend, "Quit", 484, 576, 320, 96, 48);
}

void TotalMenu::setPosition(MenuType type){
    //창, 텍스트 크기 받아오기
    int windowWidth, windowHeight, textWidth, textHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);
    TTF_SizeText(title.getFont(), "Naktris", &textWidth, &textHeight);

    //비율 조정
    WidthRatio = 0.16; // 1/6
    HeightRatio = 0.1; // 1/10
    SpacingRatio = 0.05; // 1/20
    const float buttonWidth = windowWidth / WidthRatio;
    const float buttonHeight = windowHeight / HeightRatio;
    const float buttonSpacing = windowHeight / SpacingRatio;

    // 폰트 크기를 창 높이에 비례하여 계산
    int fontSize = static_cast<int>(windowHeight * 0.05); // 폰트 크기는 창 높이의 5%
    if (fontSize < 10) fontSize = 10; // 최소 폰트 크기 제한
    if (fontSize > 100) fontSize = 100; // 최대 폰트 크기 제한
    int titleSize = static_cast<int>(windowHeight * 0.07); // 제목크기는 창 높이의 7%
    if (fontSize < 10) fontSize = 13; // 최소 폰트 크기 제한
    if (fontSize > 100) fontSize = 120; // 최대 폰트 크기 제한

    //위치할 좌표 계산
    int startX = (windowWidth - buttonWidth) / 2;
    int totalHeight = (buttonHeight * 3) + (buttonSpacing * (2));
    int startY = (windowHeight - totalHeight) / 2;
    int term = buttonHeight + buttonSpacing;

    int titleX = (windowWidth - textWidth) / 2;
    int titleY = startY-fontSize - (fontSize/2);
    title.setPosition(titleX, titleY);

    for(size_t i = 0; i<3; ++i){
        mainMenuButtons[i].setPosition(startX, startY+(i*term));
    }
}

void TotalMenu::renderMainMenu(bool isWindowResized) {
    //배경을 검은색으로 초기화
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
    SDL_RenderClear(rend);

    // 게임 이름
    int fontSize = 48;
    //SDL_font title;
    title.initFont(rend, "font", fontSize);
    SDL_Color textColor = {255, 255, 255, 255};
    title.textSetting("Naktris", textColor);
    title.setPosition(535, 230);
    title.render();
    
    if(isWindowResized){
        setPosition(MAIN);
    }

    // Made by 텍스트
    // font = TTF_OpenFont("src/assets/font.ttf", 16);
    // if (font) {
    //     SDL_Color textColor = {255, 255, 255, 255};
    //     SDL_Surface* surface = TTF_RenderText_Solid(font, "Made by nakge_hurt", textColor);
    //     SDL_Texture* texture = SDL_CreateTextureFromSurface(rend, surface);
    //     SDL_Rect destRect = {10, 580, surface->w, surface->h};
    //     SDL_RenderCopy(rend, texture, nullptr, &destRect);
    //     SDL_FreeSurface(surface);
    //     SDL_DestroyTexture(texture);
    //     TTF_CloseFont(font);
    // }

    // 버튼 렌더링
    for(size_t i = 0; i < mainMenuButtons.size(); ++i){
        mainMenuButtons[i].render();
    }
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

void TotalMenu::render(bool isWindowResized) {
    switch (currentMenu) {
        case MAIN:
            renderMainMenu(isWindowResized);
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