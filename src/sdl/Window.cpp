#include "Window.h"

Window::Window() { //생성자
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_GAMECONTROLLER) != 0) { //비디오, 타이머, 컨트롤러 설정
        std::cerr << "SDL 초기설정 실패: " << SDL_GetError() << std::endl;
        throw std::runtime_error("SDL 초기설정 실패");
    }

    window = SDL_CreateWindow( //윈도우 생성
                        "SDL2 on macOS 🍎 v" game_version , //윈도우 이름
                        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, //초기 마우스 위치
                        640, 480, //창 크기
                        SDL_WINDOW_RESIZABLE); //속성(다중 가능)
    
    if(!window){
        std::cerr << "윈도우 생성 실패" << SDL_GetError() << std::endl;
        SDL_Quit();
        throw std::runtime_error("윈도우 생성 실패");
    }

    rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC); //랜더러 설정
    if (!rend) {
        std::cerr << "랜더러 생성 실패" << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        throw std::runtime_error("랜더러 생성 실패");
    }
}

Window::~Window(){
    //SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}