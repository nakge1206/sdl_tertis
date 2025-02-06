#pragma once

#include <SDL2/SDL.h>
#include <iostream>

class Timer{
public:
    Timer();

    void start(); //타이머 시작
    void stop(); //타이머 정지
    void pause(); //타이머 일시정지
    void unPause(); //타이머 일시정지 취소
    void reset(); //타이머 리셋

    uint32_t getTicks(); //타이머 시간 받아오기(ms)

    void addTicks(int tick); //타이머 시간 더하기(ms)

    //getter
    bool isStart(); //타이머가 시작되었으면 true
    bool isPause(); //타이머가 일시정지 되어있으면 true

private:
    uint32_t StartTicks;
    uint32_t PauseTicks;

    bool Paused;
    bool Started;
};