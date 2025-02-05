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

    //getter
    bool isGameRunning();

private:
    bool GameRunning;

    //블럭이 내려가는거 구현하는 타이머
    Timer downTimer;
    float gravitySum;
    float fallInterval; //내려가는 기준. 현재 기본값은 1000ms = 1초

    //땅바닥에 멈췄을때 돌아가는 타이머
    Timer lockDelayTimer;
    u_int32_t lockDelay;

    Field* playField;
    SDL_Input* input;
    int bagNum;
    std::vector<TetroMino> tempBag;
};
