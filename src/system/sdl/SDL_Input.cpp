#include "SDL_Input.h"

// Singleton 인스턴스 가져오기
SDL_Input& SDL_Input::getInstance() {
    static SDL_Input instance;
    return instance;
}

// 생성자
SDL_Input::SDL_Input() :quitStates(false) {
    a = 10;
}

// 소멸자
SDL_Input::~SDL_Input() {}

// 이벤트 처리
void SDL_Input::processEvent(const SDL_Event& event) {
    switch (event.type) {
    case SDL_QUIT:
        quitStates = true;
    case SDL_KEYDOWN:
        keyStates[event.key.keysym.scancode] = true;
        break;
    case SDL_KEYUP:
        keyStates[event.key.keysym.scancode] = false;
        break;
    case SDL_MOUSEBUTTONDOWN:
        mouseButtonStates[event.button.button] = true;
        break;
    case SDL_MOUSEBUTTONUP:
        mouseButtonStates[event.button.button] = false;
        break;
    default:
        break;
    }
}

void SDL_Input:: createQuitEvent(){
    SDL_Event event;
    event.type = SDL_QUIT;
    SDL_Input::getInstance().processEvent(event);
}

bool SDL_Input::isQuit(){
    return quitStates;
}

// 키 상태 확인
bool SDL_Input::isKeyPressed(SDL_Scancode key) const {
    std::unordered_map<SDL_Scancode, bool>::const_iterator it = keyStates.find(key);
    return it != keyStates.end() && it->second;
}

// 마우스 버튼 상태 확인
bool SDL_Input::isMouseButtonPressed(Uint8 button) const {
    std::unordered_map<Uint8, bool>::const_iterator it = mouseButtonStates.find(button);
    return it != mouseButtonStates.end() && it->second;
}

void SDL_Input::setalpha(int b){
    a=b;
}

void SDL_Input::printalpha(){
    std::cout << a << std::endl;
}