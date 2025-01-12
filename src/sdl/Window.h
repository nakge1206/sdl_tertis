#ifndef WINDOW_H
#define WINDOW_H

#include "../definitions.h"

class Window { //초기 창 열기
private:
    SDL_Window* window;
    SDL_Renderer* rend;
public:
    Window(); //생성자


    ~Window(); //소멸자
};
#endif