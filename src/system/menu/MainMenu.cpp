#include "MainMenu.h"


MainMenu::MainMenu() : rend(nullptr), window(nullptr), mainState(NOTHING){
    isQuit = false;

    mainStart = false;
    mainSetting = false;
}

MainMenu::~MainMenu() {
}

//메인메뉴 화면 미리 정해놓기
void MainMenu::initMain(SDL_Renderer* rend, SDL_Window* window) {
    this->rend = rend; this->window = window;
    mainButtons.clear();

    //버튼 생성
    int buttonWidth = 960 * 0.2;
    int buttonHeight = 540 * 0.13;
    int buttonSpacing = 540 * 0.05;

    int startX = (960 - buttonWidth) / 2;
    int totalHeight = (buttonHeight * 3) + (buttonSpacing * (2));
    int startY = (540 - totalHeight) / 2 + (buttonHeight*0.5);
    int term = buttonHeight + buttonSpacing;

    int fontSize = 25;
    mainButtons.emplace_back();
    mainButtons.emplace_back();
    mainButtons.emplace_back();
    mainButtons[0].initButton(rend, "Start_Game", startX, startY, buttonWidth, buttonHeight, fontSize);
    mainButtons[1].initButton(rend, "Setting", startX, startY + term, buttonWidth, buttonHeight, fontSize);
    mainButtons[2].initButton(rend, "Quit", startX, startY + term + term, buttonWidth, buttonHeight, fontSize);
    /*버튼 색상 및 하이라이트 색상 바꿀 수 있음
    SDL_Color basic = {r, g, b, a};
    SDL_Color highlight = {r, g, b, a};
    
    for(size_t i=0; i<3; ++i){
        mainButton[i].setDefaultColor(basic);
        mainButton[i].setHighlightColor(highlight);
    }
    */

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

void MainMenu::render() {
    //배경을 검은색으로 초기화
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
    SDL_RenderClear(rend);
    //버튼 및 제목, 제작자 표기
    for(size_t i = 0; i < 3; ++i){
        mainButtons[i].render();
    }
    title.render();
    madeBy.render();

}

void MainMenu::handelEvent(){
    SDL_GetMouseState(&mouseX, &mouseY);
    for(size_t i=0; i<3; ++i){
        if(mainButtons[0].isMouseOver(mouseX, mouseY)){
            mainState = MAIN_START;
        } else if(mainButtons[1].isMouseOver(mouseX, mouseY)){
            mainState = MAIN_SETTING;
        } else if(mainButtons[2].isMouseOver(mouseX, mouseY)){
            mainState = MAIN_QUIT;
        }
    }

    switch (mainState){
    case NOTHING:
        mainButtons[0].setHighlight(false);
        mainButtons[1].setHighlight(false);
        mainButtons[2].setHighlight(false);
        break;
    case MAIN_START:
        mainButtons[0].setHighlight(true);
        mainButtons[1].setHighlight(false);
        mainButtons[2].setHighlight(false);
        break;
    case MAIN_SETTING:
        mainButtons[0].setHighlight(false);
        mainButtons[1].setHighlight(true);
        mainButtons[2].setHighlight(false);
        break;
    case MAIN_QUIT:
        mainButtons[0].setHighlight(false);
        mainButtons[1].setHighlight(false);
        mainButtons[2].setHighlight(true);
        break;
    default:
        break;
    }
}

void MainMenu::run(){
    handelEvent();
    render();
}

//Window에서 HandelEnvent에 따른 처리 함수
void MainMenu::UpClick(){
    switch (mainState){
    case NOTHING:
        break;
    case MAIN_START:
        break;
    case MAIN_SETTING:
        mainState = MAIN_START;
        break;
    case MAIN_QUIT:
        mainState = MAIN_SETTING;
        break;
    default:
        break;
    }
}

void MainMenu::DownClick(){
    switch (mainState){
    case NOTHING:
        mainState = MAIN_START;
        break;
    case MAIN_START:
        mainState = MAIN_SETTING;
        break;
    case MAIN_SETTING:
        mainState = MAIN_QUIT;
        break;
    case MAIN_QUIT:
        break;
    default:
        break;
    }
}

void MainMenu::EnterClick(){
    switch (mainState){
    case NOTHING:
        break;
    case MAIN_START:
        mainButtons[0].setprint();
        mainStart = true;
        break;
    case MAIN_SETTING:
        mainButtons[1].setprint();
        mainSetting = true;
        break;
    case MAIN_QUIT:
        mainButtons[2].setprint();
        isQuit = true;
        break;
    default:
        break;
    }
}

void MainMenu::OnClick(){
    SDL_GetMouseState(&mouseX, &mouseY);
    bool isMouse0 = mainButtons[0].isMouseOver(mouseX, mouseY);
    bool isMouse1 = mainButtons[1].isMouseOver(mouseX, mouseY);
    bool isMouse2 = mainButtons[2].isMouseOver(mouseX, mouseY);
    if(isMouse0){
        mainButtons[0].setprint();
        mainStart = true;
    }
    if(isMouse1){
        mainButtons[1].setprint();
        mainSetting = true;
    }
    if(isMouse2){
        mainButtons[2].setprint();
        isQuit = true;
    }
}