#include "MenuButton.h"

MenuButton::MenuButton(SDL_Renderer* rend, const std::string& text, int x, int y, int width, int height, int fontSize)
    : rend(rend), text(text), highlight(false), onClick(nullptr), fontSize(fontSize){
    rect.x= x; rect.y=y; rect.w=width; rect.h=height;

    //버튼 색상 정보
    //나중에 이거 설정할 수 있게 바꾸면 될듯(현재는 기본 검은색, 하이라이트는 노란색)
    defaultColor.r=255; defaultColor.g=255; defaultColor.b=255; defaultColor.a=255; //검은색
    highlightColor.r=211; highlightColor.g=211; highlightColor.b=211; highlightColor.a=255; //노란색
    buttonText.initFont(rend, "font", fontSize);
}

MenuButton::~MenuButton() {}

void MenuButton::render() {
    //defaultColor로 rend의 색 설정
    SDL_SetRenderDrawColor(rend, defaultColor.r, defaultColor.g, defaultColor.b, defaultColor.a);
    //rect에 rend색 입히기
    SDL_RenderFillRect(rend, &rect);
    if (highlight) {
        SDL_SetRenderDrawColor(rend, highlightColor.r, highlightColor.g, highlightColor.b, highlightColor.a);
        SDL_RenderFillRect(rend, &rect);
    }

    //글자 가운데 정렬
    SDL_Color textColor = {0, 0, 0, 255}; //검은색
    buttonText.textSetting(text, textColor);
    SDL_Rect textRect;
    textRect.w = buttonText.getSurfaceInfo('w');
    textRect.h = buttonText.getSurfaceInfo('h');
    textRect.x = rect.x + (rect.w - textRect.w) / 2;
    textRect.y = rect.y + (rect.h - textRect.h) / 2;

    buttonText.setPosition(textRect);

    buttonText.render();
}

void MenuButton::setPosition(int x, int y){
    setPosition(x, y, rect.w, rect.h, fontSize);
}

void MenuButton::setPosition(int x, int y, int w, int h, int fontSize){
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

}

void MenuButton::setPosition(SDL_Rect destRect){
    rect.x = destRect.x;
    rect.y = destRect.y;
    rect.w = destRect.w;
    rect.h = destRect.h;
}

bool MenuButton::isMouseOver(int mouseX, int mouseY) const {
    return mouseX >= rect.x && mouseX <= rect.x + rect.w &&
           mouseY >= rect.y && mouseY <= rect.y + rect.h;
}

void MenuButton::setHighlight(bool highlight) {
    this->highlight = highlight;
}

void MenuButton::setOnClick(void (*onClick)()) {
    this->onClick = onClick;
}

void MenuButton::setprint(){
    std::cout << text << " is click! " << std::endl;
}