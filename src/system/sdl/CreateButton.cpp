#include "CreateButton.h"

CreateButton::CreateButton() : rend(nullptr), highlight(false) {}
CreateButton::~CreateButton() {}

void CreateButton::initButton(SDL_Renderer* rend, const std::string& text, int x, int y, int width, int height, int fontSize, const std::string& fontName){
    this->rend = rend;
    this->text = text;
    rect.x=x; rect.y=y; rect.w=width; rect.h=height;

    //버튼 색상 정보(기본 => 검은색, 밝은회색)
    defaultColor.r=255; defaultColor.g=255; defaultColor.b=255; defaultColor.a=255;
    highlightColor.r=211; highlightColor.g=211; highlightColor.b=211; highlightColor.a=255;
    
    //글자 가운데 정렬
    buttonText.initFont(rend, fontName, fontSize);
    SDL_Color textColor = {0, 0, 0, 255}; //흰색
    buttonText.textSetting(this->text, textColor);

    buttonText.setPosition(cal_textRect());
}

void CreateButton::render() {
    //defaultColor로 색 설정 후, rect에 채우기
    SDL_SetRenderDrawColor(rend, defaultColor.r, defaultColor.g, defaultColor.b, defaultColor.a);
    SDL_RenderFillRect(rend, &rect);
    if (highlight) { //highlight가 true면, highlightColor로 rect를 채움
        SDL_SetRenderDrawColor(rend, highlightColor.r, highlightColor.g, highlightColor.b, highlightColor.a);
        SDL_RenderFillRect(rend, &rect);
    }
    buttonText.render();
}

void CreateButton::setPosition(int x, int y){
    setPosition(x, y, rect.w, rect.h);
}

void CreateButton::setPosition(int x, int y, int w, int h){
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    buttonText.setPosition(cal_textRect());
}

void CreateButton::setPosition(SDL_Rect destRect){
    rect.x = destRect.x;
    rect.y = destRect.y;
    rect.w = destRect.w;
    rect.h = destRect.h;
    buttonText.setPosition(cal_textRect());
}

void CreateButton::setDefaultColor(SDL_Color basic){
    defaultColor.r=basic.r;
    defaultColor.g=basic.g;
    defaultColor.b=basic.b;
    defaultColor.a=basic.a;
}

void CreateButton::setHighlightColor(SDL_Color highlight){
    highlightColor.r=highlight.r;
    highlightColor.g=highlight.g;
    highlightColor.b=highlight.b;
    highlightColor.a=highlight.a;
}

void CreateButton::setTextColor(const std::string& tempText, SDL_Color textColor){
    buttonText.setTextColor(tempText, textColor);
}

bool CreateButton::isMouseOver(int mouseX, int mouseY) const {
    return mouseX >= rect.x && mouseX <= rect.x + rect.w &&
           mouseY >= rect.y && mouseY <= rect.y + rect.h;
}

void CreateButton::setHighlight(bool highlight) {
    this->highlight = highlight;
}

SDL_Rect CreateButton::cal_textRect(){
    SDL_Rect textRect;
    textRect.w = buttonText.getSurfaceInfo('w');
    textRect.h = buttonText.getSurfaceInfo('h');
    textRect.x = rect.x + (rect.w - textRect.w) / 2;
    textRect.y = rect.y + (rect.h - textRect.h) / 2;
    return textRect;
}

void CreateButton::setprint(){
    std::cout << text << " is click! " << std::endl;
}