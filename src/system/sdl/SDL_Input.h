#pragma once

#include <SDL2/SDL.h>
#include <string.h>
#include <iostream>

class SDL_Input{

public:
    enum MOUSE_BUTTONS { left=0, right, middle, back, forward };
private:
    //싱글톤 구현
    static SDL_Input* sInstance;
    uint8_t* mPrevKeyboardState;
    const uint8_t* mKeyboardState;
    int mKeyLength;

    uint32_t mPrevMouseState;
    uint32_t mMouseState;

    int mMouseXPos;
    int mMouseYPos;

    uint32_t lastChecklTime;

public:
    static SDL_Input* Instance();
    static void Release();

    //키보드 처리
    bool KeyDown(SDL_Scancode scanCode);
    bool KeyPressed(SDL_Scancode scanCode);
    bool KeyReleased(SDL_Scancode scanCode);

    //마우스 처리
    bool MouseButtonDown(MOUSE_BUTTONS button);
    bool MouseButtonPressed(MOUSE_BUTTONS button);
    bool MouseButtonReleased(MOUSE_BUTTONS button);

    //상태 업데이트
    void Update();
    void UpdatePrevInput();

private:
    SDL_Input();
    ~SDL_Input();
};
