#include "MainMenu.h"

MainMenu::MainMenu() : rend(nullptr), window(nullptr), mainState(NOTHING){
    testa = true;
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

    //시험용
    // SDL_Color textcc = {0, 255, 255, 255}; //푸른색
    // mainButtons[1].setTextColor("Setting", textcc);
    // textcc.r = 255; textcc.g = 0; textcc.b = 127; textcc.a = 255; //자홍색
    // mainButtons[1].setDefaultColor(textcc);
    // mainButtons[0].setPosition(0, 0);

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

    SDL_Input& input = SDL_Input::getInstance();
    SDL_Event event;
    if(input.isKeyPressed(SDL_SCANCODE_A)) std::cout<<"click!" << std::endl;
    //화살표로 상태고정기능
    switch (mainState) {
        case NOTHING:
            if(input.isKeyPressed(SDL_SCANCODE_DOWN)) mainState = MAIN_START;
            break;
        case MAIN_START:
            mainButtons[0].setHighlight(true);
            if(input.isKeyPressed(SDL_SCANCODE_KP_ENTER)) mainButtons[0].setprint();
            if(input.isKeyPressed(SDL_SCANCODE_UP)) mainState = NOTHING;
            else if(input.isKeyPressed(SDL_SCANCODE_DOWN)) mainState = MAIN_SETTING;
            break;
        case MAIN_SETTING:
            mainButtons[1].setHighlight(true);
            if(input.isKeyPressed(SDL_SCANCODE_KP_ENTER)) mainButtons[1].setprint();
            if(input.isKeyPressed(SDL_SCANCODE_UP)) mainState = MAIN_START;
            else if(input.isKeyPressed(SDL_SCANCODE_DOWN)) mainState = MAIN_QUIT;
            break;
        case MAIN_QUIT:
            mainButtons[2].setHighlight(true);
            if(input.isKeyPressed(SDL_SCANCODE_KP_ENTER)) mainButtons[2].setprint();
            if(input.isKeyPressed(SDL_SCANCODE_UP)) mainState = MAIN_SETTING;
            break;
        default:
            break;
    }
    

    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    for(size_t i=0; i<3; ++i){
        bool isMouse = mainButtons[i].isMouseOver(mouseX, mouseY);
        //마우스가 위에 올라가면 하이라이트 표시
        mainButtons[i].setHighlight(isMouse);
        //버튼 클릭시.
        if(isMouse && input.isMouseButtonPressed(SDL_BUTTON_LEFT)){
            mainButtons[i].setprint();
            if(i == 2) input.createQuitEvent();
            if(testa) input.printalpha();
        }
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