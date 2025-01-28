#include "GameMenu.h"


GameMenu::GameMenu() : rend(nullptr), window(nullptr), gameMenuState(NOTHING){
    isBack = false;
}

GameMenu::~GameMenu() {
}

//초기화
void GameMenu::initGameMenu(SDL_Renderer* rend, SDL_Window* window) {
    this->rend = rend; this->window = window;
    mainButtons.clear();

    //버튼 생성
    int buttonWidth = 960 * 0.25;
    int buttonHeight = 540 * 0.13;
    int buttonSpacing = 540 * 0.05;

    int startX = (960 - buttonWidth) / 2 - (buttonWidth*0.9);
    int totalHeight = (buttonHeight * 4) + (buttonSpacing * 3);
    int startY = (540 - totalHeight) / 2;
    int term = buttonHeight + buttonSpacing;

    int fontSize = 25;
    mainButtons.emplace_back();
    mainButtons.emplace_back();
    mainButtons.emplace_back();
    mainButtons.emplace_back();
    mainButtons[0].initButton(rend, "Single 40Line", startX, startY, buttonWidth, buttonHeight, fontSize);
    mainButtons[1].initButton(rend, "Single 1Minute", startX, startY + term, buttonWidth, buttonHeight, fontSize);
    mainButtons[2].initButton(rend, "Single vs AI", startX, startY + (term*2), buttonWidth, buttonHeight, fontSize);
    mainButtons[3].initButton(rend, "Multi", startX, startY + (term*3), buttonWidth, buttonHeight, fontSize);
    /*버튼 색상 및 하이라이트 색상 바꿀 수 있음
    SDL_Color basic = {r, g, b, a};
    SDL_Color highlight = {r, g, b, a};
    
    for(size_t i=0; i<4; ++i){
        mainButton[i].setDefaultColor(basic);
        mainButton[i].setHighlightColor(highlight);
    }
    */

    //뒤로가기
    back = CreateButton();
    back.initButton(rend, "Back (B)", 10, 10, 70, 30, 12);

    //게임 설명
    fontSize = 30;
    SDL_Color textColor = {255, 255, 255, 255};
    int textX = startX + (buttonWidth*1.2);
    int textY = startY + (term*0.15);

    guide_40.initFont(rend, "font", fontSize);
    guide_ai.initFont(rend, "font", fontSize);
    fontSize = 25;
    guide_1m.initFont(rend, "font", fontSize);
    guide_multi.initFont(rend, "font", fontSize);
    
    guide_40.textSetting("Erase 40 lines quickly!", textColor);
    guide_1m.textSetting("Erase a lot of lines for a minute!", textColor);
    guide_ai.textSetting("Battle AI!", textColor);
    guide_multi.textSetting("A one-on-one match with a friend!", textColor);

    guide_40.setPosition(textX, textY);
    guide_1m.setPosition(textX, textY+term);
    guide_ai.setPosition(textX, textY+(term*2));
    guide_multi.setPosition(textX, textY+(term*3));
    /*
    int titleWidth = title.getSurfaceInfo('w');
    int titleHeight = title.getSurfaceInfo('h');
    int titleX = (960 - titleWidth) / 2;
    int titleY = ((540 - totalHeight) / 2) - (titleHeight);
    title.setPosition(titleX, titleY);
    */
}

void GameMenu::render() {
    //배경을 검은색으로 초기화
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
    SDL_RenderClear(rend);
    //버튼 및 제목, 제작자 표기
    for(size_t i = 0; i < 4; ++i){
        mainButtons[i].render();
    }
    back.render();
    guide_40.render();
    guide_1m.render();
    guide_ai.render();
    guide_multi.render();
}

void GameMenu::handelEvent(){
    SDL_GetMouseState(&mouseX, &mouseY);
    for(size_t i=0; i<4; ++i){
        if(mainButtons[0].isMouseOver(mouseX, mouseY)){
            gameMenuState = SINGLE40;
        }else if(mainButtons[1].isMouseOver(mouseX, mouseY)){
            gameMenuState = SINGLE1M;
        }else if(mainButtons[2].isMouseOver(mouseX, mouseY)){
            gameMenuState = SINGLEAI;
        }else if(mainButtons[3].isMouseOver(mouseX, mouseY)){
            gameMenuState = MULTI;
        }
    }
    if(back.isMouseOver(mouseX, mouseY)) back.setHighlight(true);
    else back.setHighlight(false);

    switch (gameMenuState){
    case NOTHING:
        mainButtons[0].setHighlight(false);
        mainButtons[1].setHighlight(false);
        mainButtons[2].setHighlight(false);
        mainButtons[3].setHighlight(false);
        break;
    case SINGLE40:
        mainButtons[0].setHighlight(true);
        mainButtons[1].setHighlight(false);
        mainButtons[2].setHighlight(false);
        mainButtons[3].setHighlight(false);
        break;
    case SINGLE1M:
        mainButtons[0].setHighlight(false);
        mainButtons[1].setHighlight(true);
        mainButtons[2].setHighlight(false);
        mainButtons[3].setHighlight(false);
        break;
    case SINGLEAI:
        mainButtons[0].setHighlight(false);
        mainButtons[1].setHighlight(false);
        mainButtons[2].setHighlight(true);
        mainButtons[3].setHighlight(false);
        break;
    case MULTI:
        mainButtons[0].setHighlight(false);
        mainButtons[1].setHighlight(false);
        mainButtons[2].setHighlight(false);
        mainButtons[3].setHighlight(true);
        break;
    default:
        break;
    }
}

void GameMenu::run(){
    handelEvent();
    render();
}

//Window에서 HandelEnvent에 따른 처리 함수
void GameMenu::UpClick(){
    switch (gameMenuState){
    case NOTHING:
        break;
    case SINGLE40:
        break;
    case SINGLE1M:
        gameMenuState = SINGLE40;
        break;
    case SINGLEAI:
        gameMenuState = SINGLE1M;
        break;
    case MULTI:
        gameMenuState = SINGLEAI;
        break;
    default:
        break;
    }
}

void GameMenu::DownClick(){
    switch (gameMenuState){
    case NOTHING:
        gameMenuState = SINGLE40;
        break;
    case SINGLE40:
        gameMenuState = SINGLE1M;
        break;
    case SINGLE1M:
        gameMenuState = SINGLEAI;
        break;
    case SINGLEAI:
        gameMenuState = MULTI;
        break;
    case MULTI:
        break;
    default:
        break;
    }
}

void GameMenu::EnterClick(){
    switch (gameMenuState){
    case NOTHING:
        break;
    case SINGLE40:
        mainButtons[0].setprint();
        break;
    case SINGLE1M:
        mainButtons[1].setprint();
        break;
    case SINGLEAI:
        mainButtons[2].setprint();
        break;
    case MULTI:
        mainButtons[3].setprint();
        break;
    default:
        break;
    }
}

void GameMenu::OnClick(){
    SDL_GetMouseState(&mouseX, &mouseY);
    bool isMouse0 = mainButtons[0].isMouseOver(mouseX, mouseY);
    bool isMouse1 = mainButtons[1].isMouseOver(mouseX, mouseY);
    bool isMouse2 = mainButtons[2].isMouseOver(mouseX, mouseY);
    bool isMouse3 = mainButtons[3].isMouseOver(mouseX, mouseY);
    bool isMouseBack = back.isMouseOver(mouseX, mouseY);
    if(isMouse0){
        mainButtons[0].setprint();
    }
    if(isMouse1){
        mainButtons[1].setprint();
    }
    if(isMouse2){
        mainButtons[2].setprint();
    }
    if(isMouse3){
        mainButtons[3].setprint();
    }
    if(isMouseBack){
        back.setprint();
        isBack = true;
    }
}