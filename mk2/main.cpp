#include <SDL2/SDL.h>
#include <ctime> //time() 함수
#include <cstdlib> //rand() 함수
#include <vector>
#include <iostream>


#define FIELD_WIDTH 10 //가로 10줄
#define FIELD_HEIGHT 20 //세로 20줄

#define WIDTH 960
#define HEIGHT 540
#define TILE_SIZE 32

#define game_version "1.0"

uint32_t frameStart;
int frameTime;
const int FPS = 60;
const int FRAME_DELAY = 1000/FPS;

// int frameCount, timeFPS, lastFrame, fps;
bool left, right, up, down;
bool isRunning;

SDL_Window* window;
SDL_Renderer* rend;
SDL_Rect rect;

struct block{
    SDL_Color color;
    bool active;
};

struct shape{
    SDL_Color color;
    bool matrix[4][4];
    double x, y;
    int size;
};

shape blocks[7] = {
    {{255, 165, 0}, //L Mino
    {{0, 0, 1, 0}
    ,{1, 1, 1, 0}
    ,{0, 0, 0, 0}
    ,{0, 0, 0, 0}}
    , 5, 4, 3}
    ,{{255, 0, 0}, //Z Mino
    {{1, 1, 0, 0}
    ,{0, 1, 1, 0}
    ,{0, 0, 0, 0}
    ,{0, 0, 0, 0}}
    , 5, 4, 3}
    ,{{253, 255, 255}, //I Mino
    {{1, 1, 1, 1}
    ,{0, 0, 0, 0}
    ,{0, 0, 0, 0}
    ,{0, 0, 0, 0}}
    , 5, 4, 4}
    ,{{0, 0, 255}, //J Mino
    {{1, 0, 0, 0}
    ,{1, 1, 1, 0}
    ,{0, 0, 0, 0}
    ,{0, 0, 0, 0}}
    , 5, 4, 3}
    ,{{255, 255, 0}, //O Mino
    {{1, 1, 0, 0}
    ,{1, 1, 0, 0}
    ,{0, 0, 0, 0}
    ,{0, 0, 0, 0}}
    , 5, 4, 2}
    ,{{0, 0, 255}, //S Mino
    {{0, 1, 1, 0}
    ,{1, 1, 0, 0}
    ,{0, 0, 0, 0}
    ,{0, 0, 0, 0}}
    , 5, 4, 3}
    , {{128, 0, 128}, //T Mino
    {{0, 1, 0, 0}
    ,{1, 1, 1, 0}
    ,{0, 0, 0, 0}
    ,{0, 0, 0, 0}}
    , 5, 4, 3}
    };

shape cur;


shape reverseCols(shape s){
    shape tmp = s;
    for(int i=0; i<s.size; i++){
        for(int j=0; i<s.size/2; j++){
            bool t = s.matrix[i][j];
            tmp.matrix[i][j] = s.matrix[i][s.size-j-i];
            tmp.matrix[i][s.size-j-1] = t;
        }
    }
    return tmp;
}

shape transepose(shape s) {
    shape tmp = s;
    for(int i=0; i<s.size; i++){
        for(int j=0; i<s.size; j++){
            tmp.matrix[i][j] = s.matrix[j][i];
        }
    }
    return tmp;
}

void rotate(){
    cur = reverseCols(transepose(cur));
}
 
void draw(shape s){
    for(int i=0; i<s.size; i++){
        for(int j=0; j<s.size; j++){
            if(s.matrix[i][j]){
                //여기서 s.x, s.y의 기준은 게임 시작 시 그리드의 좌표.
                rect.x = (s.x+j)*TILE_SIZE; 
                rect.y = (s.y+i)*TILE_SIZE;
                SDL_SetRenderDrawColor(rend, s.color.r, s.color.g, s.color.b, 255);
                SDL_RenderFillRect(rend, &rect);
                SDL_SetRenderDrawColor(rend, 219, 219, 219, 255);
                SDL_RenderDrawRect(rend, &rect);
            }
        }
    }
}

void HandleEvents(){
    SDL_Event event;
    SDL_PollEvent(&event);
    if(event.type == SDL_QUIT) isRunning = false;
}

void Update(){

}

void Render(){
    //화면 검은색으로 초기화
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
    SDL_RenderClear(rend);

    draw(cur);

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
    cur = blocks[6];

    rect.w = TILE_SIZE;
    rect.h = TILE_SIZE;

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
