#include "MenuButton.h"

MenuButton::MenuButton(SDL_Renderer* renderer, const std::string& text, int x, int y, int width, int height, int fontSize)
    : renderer(renderer), text(text), highlight(false), onClick(nullptr), fontSize(fontSize){
    rect.x= x; rect.y=y; rect.w=width; rect.h=height;

    //버튼 색상 정보
    //나중에 이거 설정할 수 있게 바꾸면 될듯(현재는 기본 검은색, 하이라이트는 노란색)
    defaultColor.r=255; defaultColor.g=255; defaultColor.b=255; defaultColor.a=255; //검은색
    highlightColor.r=255; highlightColor.g=255; highlightColor.b=0; highlightColor.a=255; //노란색
}

MenuButton::~MenuButton() {}

void MenuButton::render() {
    SDL_SetRenderDrawColor(renderer, defaultColor.r, defaultColor.g, defaultColor.b, defaultColor.a);
    SDL_RenderFillRect(renderer, &rect);
    if (highlight) {
        SDL_SetRenderDrawColor(renderer, highlightColor.r, highlightColor.g, highlightColor.b, highlightColor.a);
        SDL_RenderDrawRect(renderer, &rect);
    }

    // 텍스트 렌더링 (TTF 필요)
    TTF_Font* font = TTF_OpenFont("src/assets/font.ttf", fontSize);
    if (!font) {
        std::cerr << "폰트 불러오기 오류: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Color textColor = {0, 0, 0, 255}; //검은색
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    if (!textSurface) {
        std::cerr << "텍스트 렌더링 오류: " << TTF_GetError() << std::endl;
        return;
    }
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!textTexture) {
        std::cerr << "텍스처 생성 오류: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(textSurface);
        return;
    }

    //텍스트 가운데 정렬
    SDL_Rect textRect;
    textRect.w = textSurface->w;
    textRect.h = textSurface->h;
    textRect.x = rect.x + (rect.w - textRect.w) / 2; // 버튼 중앙에 텍스트 정렬
    textRect.y = rect.y + (rect.h - textRect.h) / 2;

    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);
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