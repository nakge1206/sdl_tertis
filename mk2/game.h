#pragma once

#include "Field.h"
#include "TetroMino.h"
#include "SDL_Input.h"
#include "Timer.h"

class game{
public:
//todo: clear(재시작) 기능 추가해야할거 같음.
    game();
    ~game();

    void handleEvent();
    void render(SDL_Renderer* rend);
    void start();
    void tick();

    void moveUpdate();

    //getter
    bool isGameRunning();

private:
    bool GameRunning;

    Field* playField;
    SDL_Input* input;

    //블럭이 내려가는거 구현하는 타이머
    Timer downTimer;
    float gravitySum;
    float fallInterval; //내려가는 기준. 현재 기본값은 1000ms = 1초

    //땅바닥에 멈췄을때 돌아가는 타이머
    Timer lockDelayTimer;
    uint32_t lockDelay; //기본값은 500 = 0.5초 지나면 Lock됨.

    //DAS(Delayed Auto Shift) 구현
    Timer DAS_Timer;
    bool DAS_DOWN;
    bool DAS_LEFT;
    bool DAS_RIGHT;
    uint32_t DAS_Delay;

    //디버그용
    int bagNum;
    std::vector<TetroMino> tempBag;
    void resetBag();
};
