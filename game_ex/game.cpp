#include <SDL2/SDL.h>
#include <ctime> //time() 함수
#include <cstdlib> //rand() 함수
#include <vector>
#include <iostream>

#define WIDTH 300
#define HEIGHT 300
#define TILE_SIZE 22

int frameCount, timeFPS, lastFrame, fps;
bool left, right, up, down;
bool isRunning;

SDL_Window* window;
SDL_Renderer* rend;

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
    , 5, 4, 3}}, cur;


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

SDL_Rect rect; 
void draw(shape s){
    for(int i=0; i<s.size; i++){
        for(int j=0; j<s.size; j++){
            if(s.matrix[i][j]){
                rect.x = (s.x+i)*TILE_SIZE; 
                rect.y = (rect.y+j)*TILE_SIZE;
                SDL_SetRenderDrawColor(rend, s.color.r, s.color.g, s.color.b, 255);
                SDL_RenderFillRect(rend, &rect);
                SDL_SetRenderDrawColor(rend, 219, 219, 219, 255);
                SDL_RenderDrawRect(rend, &rect);
            }
        }
    }
}

void update(){

}

void input(){

}

void render(){
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
    SDL_RenderClear(rend);

    // frameCount++;
    // int timerFPS = SDL_GetTicks()-lastFrame;
    // if(timerFPS < (1000/60)){
    //     SDL_Delay((1000/60)-timerFPS);
    // }

    draw(cur);

    SDL_RenderPresent(rend);
}

int main(int argc, char* args[]){
    int seed = time(NULL);
    srand(seed);
    cur = blocks[rand() % 7];
     
    isRunning = true;
    static int lastTime = 0;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER) < 0) std::cout << "Failed at SDL_Init()" << std::endl;

    window = SDL_CreateWindow( //윈도우 생성
                        "Tetris" //윈도우 이름
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

    // if(SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &rend) <0) std::cout << "Failed at SDL_Create()" << std::endl;
    // SDL_SetWindowTitle(window, "Tetris");

    while(isRunning){
        // lastFrame=SDL_GetTicks();
        // if(lastFrame>=(lastTime+1000)){
        //     lastTime = lastFrame;
        //     fps=frameCount;
        //     frameCount=0;
        // }
        update();
        input();
        render();
    }
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return -1;
}
