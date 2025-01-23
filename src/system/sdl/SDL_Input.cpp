#include "SDL_Input.h"

SDL_Input* SDL_Input::sInstance = NULL;

SDL_Input* SDL_Input::Instance() {
    if(sInstance == NULL){
        sInstance = new SDL_Input();
    }
    return sInstance;
}

void SDL_Input::Release(){
    delete sInstance;
    sInstance = NULL;
}

SDL_Input::SDL_Input(){
    mKeyboardState = SDL_GetKeyboardState(&mKeyLength);
    mPrevKeyboardState = new uint8_t[mKeyLength];
    memcpy(mPrevKeyboardState, mKeyboardState, mKeyLength);
}

SDL_Input::~SDL_Input(){
    delete[] mPrevKeyboardState;
    mPrevKeyboardState = NULL;
}

bool SDL_Input::KeyDown(SDL_Scancode scanCode){
    return mKeyboardState[scanCode];
}

bool SDL_Input::KeyPressed(SDL_Scancode scanCode){
    return !mPrevKeyboardState[scanCode] && mKeyboardState[scanCode];
}

bool SDL_Input::KeyReleased(SDL_Scancode scanCode){
    return mPrevKeyboardState[scanCode] && !mKeyboardState[scanCode];
}

bool SDL_Input::MouseButtonDown(MOUSE_BUTTONS button){
    uint32_t mask = 0;
    switch (button)
    {
    case left:
        mask = SDL_BUTTON_LMASK;
        break;
    case right:
        mask = SDL_BUTTON_RMASK;
        break;
    case middle:
        mask = SDL_BUTTON_MMASK;
        break;
    case back:
        mask = SDL_BUTTON_X1MASK;
        break;
    case forward:
        mask = SDL_BUTTON_X2MASK;
        break;
    default:
        break;
    }

    return (mMouseState & mask);
}

bool SDL_Input::MouseButtonPressed(MOUSE_BUTTONS button){
    uint32_t mask = 0;
    switch (button)
    {
    case left:
        mask = SDL_BUTTON_LMASK;
        break;
    case right:
        mask = SDL_BUTTON_RMASK;
        break;
    case middle:
        mask = SDL_BUTTON_MMASK;
        break;
    case back:
        mask = SDL_BUTTON_X1MASK;
        break;
    case forward:
        mask = SDL_BUTTON_X2MASK;
        break;
    default:
        break;
    }

    return !(mPrevMouseState & mask) && (mMouseState & mask);
}

bool SDL_Input::MouseButtonReleased(MOUSE_BUTTONS button){
    uint32_t mask = 0;
    switch (button)
    {
    case left:
        mask = SDL_BUTTON_LMASK;
        break;
    case right:
        mask = SDL_BUTTON_RMASK;
        break;
    case middle:
        mask = SDL_BUTTON_MMASK;
        break;
    case back:
        mask = SDL_BUTTON_X1MASK;
        break;
    case forward:
        mask = SDL_BUTTON_X2MASK;
        break;
    default:
        break;
    }

    return (mPrevMouseState & mask) && !(mMouseState & mask);
}

void SDL_Input::Update(){
    mMouseState = SDL_GetMouseState(&mMouseXPos, &mMouseYPos);
}

void SDL_Input::UpdatePrevInput(){
    memcpy(mPrevKeyboardState, mKeyboardState, mKeyLength);
    mPrevMouseState = mMouseState; 
}