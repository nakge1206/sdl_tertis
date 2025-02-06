#include <SDL2/SDL.h>
#include <ctime> //time() 함수
#include <cstdlib> //rand() 함수
#include <vector>
#include <iostream>

#include "SDL_Input.h"
#include "game.h"

#define WIDTH 960
#define HEIGHT 540
#define game_version "1.0"

SDL_Input* input = SDL_Input::Instance();

uint32_t frameStart;
int frameTime;
const int FPS = 60;
const int FRAME_DELAY = 1000/FPS;

bool isRunning;

SDL_Window* window;
SDL_Renderer* rend;

game Game;


void HandleEvents(){
    SDL_Event event;
    SDL_PollEvent(&event);
    if(event.type == SDL_QUIT) isRunning = false;
    input->Update();

    if(Game.isGameRunning()){
        Game.handleEvent();
    }
    if(!Game.isGameRunning()){
        if(input->KeyPressed(SDL_SCANCODE_BACKSPACE)){
            std::cout << "backspace" << std::endl;
            Game.start();
        }
    }

    input->UpdatePrevInput();
}

void Update(){
    Game.tick();
    Game.moveUpdate();
}

void Render(){
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
    SDL_RenderClear(rend);

    Game.render(rend);

    // 결과 화면에 출력
    SDL_RenderPresent(rend);
}

int main(int argc, char* args[]){
    //init
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_EVENTS) != 0) { //비디오, 타이머 설정
        std::cerr << "SDL 초기설정 실패: " << SDL_GetError() << std::endl;
        return -1;
    }
    // if(TTF_Init() == -1){
    //     std::cerr << "폰트설정 실패: " <<SDL_GetError() << std::endl;
    //     return -1;
    // }

    //create window & renderer
    window = SDL_CreateWindow( //윈도우 생성
                        "SDL2 on macOS 🍎 v" game_version //윈도우 이름
                        , SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED //초기 마우스 위치
                        , WIDTH, HEIGHT //창 크기
                        , 0);
                        //, SDL_WINDOW_RESIZABLE); //속성(다중 가능)
    if(!window){
        std::cerr << "윈도우 생성 실패" << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }
    rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC); //랜더러 설정
    if (!rend) {
        std::cerr << "랜더러 생성 실패" << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    isRunning = true;
    Game.start();

    while(isRunning){
        frameStart = SDL_GetTicks();

        HandleEvents();
        Update();
        Render();

        frameTime = SDL_GetTicks() - frameStart;
        if(FRAME_DELAY > frameTime) {
            SDL_Delay(FRAME_DELAY - frameTime);
        }
    }

    return 0;    
}
