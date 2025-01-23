#pragma once
#include <SDL2/SDL.h>
#include <unordered_map>
#include <iostream>

class SDL_Input {
public:
    // Singleton 패턴으로 구현 (옵션)
    static SDL_Input& getInstance();

    // 이벤트 처리 함수
    void processEvent(const SDL_Event& event);

    // 특정 키가 눌렸는지 확인
    bool isKeyPressed(SDL_Scancode key) const ;
    bool isMouseButtonPressed(Uint8 button) const;

    //종료 상태인지 확인
    bool isQuit();

    //커스텀 종료 이벤트 추가
    void createQuitEvent();

    //디버그용 함수
    void setalpha(int b);
    void printalpha();

private:
    // 생성자/소멸자
    SDL_Input();
    ~SDL_Input();
    

    // 키와 마우스 상태 저장
    std::unordered_map<SDL_Scancode, bool> keyStates; //키 상태 저장
    std::unordered_map<Uint8, bool> mouseButtonStates; //마우스버튼 상태 저장
    bool quitStates;

    //디버그용 변수
    int a;
    };