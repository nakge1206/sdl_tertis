#include "MenuCreate.h"

//메뉴(메인, 일시정지, 세팅) 초기설정

MenuCreate::MenuCreate(SDL_Renderer* renderer, SDL_Window* window)
    : renderer(renderer), window(window) {}

MenuCreate::~MenuCreate() {}

void MenuCreate::initButtons(const std::vector<std::string>& buttonText){
    buttons.clear();

    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    const float buttonWidthRatio = 0.25f;  // 버튼 너비 비율
    const float buttonHeightRatio = 0.1f;  // 버튼 높이 비율
    const float buttonSpacingRatio = 0.05f; // 버튼 간격 비율

    int buttonWidth = static_cast<int>(windowWidth * buttonWidthRatio);
    int buttonHeight = static_cast<int>(windowHeight * buttonHeightRatio);
    int buttonSpacing = static_cast<int>(windowHeight * buttonSpacingRatio);
    
    // 폰트 크기를 창 높이에 비례하여 계산
    int fontSize = static_cast<int>(windowHeight * 0.05); // 폰트 크기는 창 높이의 5%
    if (fontSize < 10) fontSize = 10; // 최소 폰트 크기 제한
    if (fontSize > 100) fontSize = 100; // 최대 폰트 크기 제한

    int totalHeight = (buttonHeight * buttonText.size()) + (buttonSpacing * (buttonText.size() - 1));
    int startY = (windowHeight - totalHeight) / 2;

    for (size_t i = 0; i < buttonText.size(); ++i) {
        int buttonX = (windowWidth - buttonWidth) / 2;
        int buttonY = startY + i * (buttonHeight + buttonSpacing);

        buttons.emplace_back(renderer, buttonText[i], buttonX, buttonY, buttonWidth, buttonHeight, fontSize);
    }
}

void MenuCreate::render(){
    for (size_t i = 0; i < buttons.size(); ++i) {
        buttons[i].render();
    }
}