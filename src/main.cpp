#include "definitions.h"

#define FIELD_WIDTH 10 //가로 10줄
#define FIELD_HEIGHT 20 //세로 20줄

int main(int argc, char* args[]){
    //그래픽, 타이머 초기설정
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    //창 설정. 이거 하고 난 다음에 render를 해주면 그래픽을 위에 입힐 수 있다고 함.
    SDL_Window* window = SDL_CreateWindow("Hello, SDL2 on macOS 🍎",
                                        SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED,
                                        640, 480, SDL_WINDOW_RESIZABLE);
    if (!window) {
        printf("창 생성 실패 : %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    //render 설정.
    SDL_Renderer* rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    if (!rend) {
        SDL_LogError(0, "랜더러 생성 실패 : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }


    // SDL_QUIT 이벤트가 발생될때까지 창을 계속 띄워두는 코드 부분
    bool running = true;
    while (running)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                running = false;
                break;
            }
        }
     }

    // clean up resources before exiting.
    SDL_DestroyWindow(window);
    SDL_Quit();
}
