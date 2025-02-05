#include "Timer.h"

Timer::Timer(){
    StartTicks = 0;
    PauseTicks = 0;
    Paused = false;
    Started = false;
}

void Timer::start(){
    Started = true;
    Paused = false;

    StartTicks = SDL_GetTicks();
    PauseTicks = 0;
}

void Timer::stop(){
    Started = false;
    Paused = false;
}

void Timer::pause(){
    if(Started && !Paused){
        Paused = true;
        PauseTicks = SDL_GetTicks() - StartTicks;
        StartTicks = 0;
    }
}

void Timer::unPause(){
    if(Started && Paused){
        Paused = false;
        StartTicks = SDL_GetTicks() - PauseTicks;
        PauseTicks = 0;
    }
}

void Timer::reset(){
    if(Started) start();
}

void Timer::addTicks(int tick){
    StartTicks -= tick;
}

uint32_t Timer::getTicks(){
    uint32_t time = 0;
    if(Started){
        if(Paused){
            time = PauseTicks;
        }else{
            time = SDL_GetTicks() - StartTicks;
        }
    }
    return time;
}

bool Timer::isStart(){
    return Started;
}

bool Timer::isPause(){
    return Paused;
}