#include "definitions.h"
#include "Window.h"

#define FIELD_WIDTH 10 //가로 10줄
#define FIELD_HEIGHT 20 //세로 20줄

int main(int argc, char* args[]){
    Window win;

    // SDL_QUIT 이벤트가 발생될때까지 창을 계속 띄워두는 코드 부분
    bool running = true;
    while (running)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0){
            if (e.type == SDL_QUIT) {
                running = false;
                break;
            }
        }
        
     }
    
}
