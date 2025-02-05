#pragma once

#include <SDL2/SDL.h>
#include <iostream>

class Timer{
public:
    Timer();

    void start();
    void stop();
    void pause();
    void unPause();
    void reset();

    uint32_t getTicks();

    void addTicks(int tick);

    //getter
    bool isStart();
    bool isPause();

private:
    uint32_t StartTicks;
    uint32_t PauseTicks;

    bool Paused;
    bool Started;
};