#include "TotalMenu.h"
#include <SDL_ttf.h>
#include <iostream>

TotalMenu::TotalMenu(SDL_Renderer* rend, SDL_Window* window)
    : rend(rend), window(window), currentMenu(MAIN), pauseBackgroundAlpha(128) {}

TotalMenu::~TotalMenu() {}

//이건 메뉴 버튼 초기화 하는거임.
void TotalMenu::initMainMenu() {
    mainMenuButtons.clear();

    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    const float buttonWidth = windowWidth / 4; //0.25
    const float buttonHeight = windowHeight / 10; //0.1
    const float buttonSpacing = windowHeight / 20; //0.05

    // 폰트 크기를 창 높이에 비례하여 계산
    int fontSize = static_cast<int>(windowHeight * 0.05); // 폰트 크기는 창 높이의 5%
    if (fontSize < 10) fontSize = 10; // 최소 폰트 크기 제한
    if (fontSize > 100) fontSize = 100; // 최대 폰트 크기 제한

    int totalHeight = (buttonHeight * 3) + (buttonSpacing * (2));
    int startY = (windowHeight - (3 * buttonHeight + 2 * buttonSpacing)) / 2;

    mainMenuButtons.emplace_back(rend, "Start Game", (windowWidth - buttonWidth) / 2, startY, buttonWidth, buttonHeight, fontSize);
    mainMenuButtons.emplace_back(rend, "Settings", (windowWidth - buttonWidth) / 2, startY + buttonHeight + buttonSpacing, buttonWidth, buttonHeight, fontSize);
    mainMenuButtons.emplace_back(rend, "Quit", (windowWidth - buttonWidth) / 2, startY + 2 * (buttonHeight + buttonSpacing), buttonWidth, buttonHeight, fontSize);
}

void TotalMenu::initPauseMenu() {
    pauseMenuButtons.clear();

    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    const int buttonWidth = windowWidth / 4;
    const int buttonHeight = windowHeight / 10;
    const int buttonSpacing = windowHeight / 20;

    int startY = (windowHeight - (3 * buttonHeight + 2 * buttonSpacing)) / 2;

    pauseMenuButtons.emplace_back(rend, "Continue", (windowWidth - buttonWidth) / 2, startY, buttonWidth, buttonHeight);
    pauseMenuButtons.emplace_back(rend, "Settings", (windowWidth - buttonWidth) / 2, startY + buttonHeight + buttonSpacing, buttonWidth, buttonHeight);
    pauseMenuButtons.emplace_back(rend, "Exit Game", (windowWidth - buttonWidth) / 2, startY + 2 * (buttonHeight + buttonSpacing), buttonWidth, buttonHeight);
}

void TotalMenu::initSettingMenu() {
    settingMenuButtons.clear();

    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    const int labelWidth = windowWidth / 3;
    const int buttonWidth = windowWidth / 6;
    const int buttonHeight = windowHeight / 10;
    const int buttonSpacing = windowHeight / 20;

    int startY = (windowHeight - (3 * buttonHeight + 2 * buttonSpacing)) / 2;

    settingMenuButtons.emplace_back(rend, "Toggle Option 1", labelWidth + buttonWidth, startY, buttonWidth, buttonHeight);
    settingMenuButtons.emplace_back(rend, "Toggle Option 2", labelWidth + buttonWidth, startY + buttonHeight + buttonSpacing, buttonWidth, buttonHeight);
    settingMenuButtons.emplace_back(rend, "Toggle Option 3", labelWidth + buttonWidth, startY + 2 * (buttonHeight + buttonSpacing), buttonWidth, buttonHeight);
}

void TotalMenu::renderMainMenu() {
    // 배경
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
    SDL_RenderClear(rend);

    // 게임 이름
    TTF_Font* font = TTF_OpenFont("src/assets/font.ttf", 48);
    if (font) {
        SDL_Color textColor = {255, 255, 255, 255};
        SDL_Surface* surface = TTF_RenderText_Solid(font, "Naktris", textColor);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(rend, surface);
        SDL_Rect destRect = {50, 50, surface->w, surface->h};
        SDL_RenderCopy(rend, texture, nullptr, &destRect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
        TTF_CloseFont(font);
    }

    // Made by 텍스트
    font = TTF_OpenFont("src/assets/font.ttf", 16);
    if (font) {
        SDL_Color textColor = {255, 255, 255, 255};
        SDL_Surface* surface = TTF_RenderText_Solid(font, "Made by nakge_hurt", textColor);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(rend, surface);
        SDL_Rect destRect = {10, 580, surface->w, surface->h};
        SDL_RenderCopy(rend, texture, nullptr, &destRect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
        TTF_CloseFont(font);
    }

    // 버튼 렌더링
    for(size_t i = 0; i < mainMenuButtons.size(); ++i){
        mainMenuButtons[i].render();
    }
}

void TotalMenu::renderPauseMenu() {
    // 어두운 배경
    SDL_SetRenderDrawColor(rend, 0, 0, 0, pauseBackgroundAlpha);
    SDL_RenderFillRect(rend, nullptr);

    // for (auto& button : pauseMenuButtons) {
    //     button.render();
    // }
}

void TotalMenu::renderSettingMenu() {
    // 배경
    SDL_SetRenderDrawColor(rend, 50, 50, 50, 255);
    SDL_RenderClear(rend);

    // for (auto& button : settingMenuButtons) {
    //     button.render();
    // }
}

void TotalMenu::render() {
    switch (currentMenu) {
        case MAIN:
            renderMainMenu();
            break;
        case PAUSE:
            renderPauseMenu();
            break;
        case SETTING:
            renderSettingMenu();
            break;
    }
}

void TotalMenu::setMenu(MenuType menu) {
    currentMenu = menu;
}

MenuType callType(int num){
    switch (num){
    case 0:
        return MenuType::MAIN;
    case 1:
        return MenuType::PAUSE;
    case 2:
        return MenuType::SETTING;
    default:
        break;
    }
}