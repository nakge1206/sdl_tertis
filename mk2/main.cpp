#include <SDL2/SDL.h>
#include <ctime> //time() 함수
#include <cstdlib> //rand() 함수
#include <vector>
#include <iostream>

#include "SDL_Input.h"
#include "TetriMino.h"


#define FIELD_WIDTH 10 //가로 10줄
#define FIELD_HEIGHT 20 //세로 20줄

#define WIDTH 960
#define HEIGHT 540
#define TILE_SIZE 22

#define game_version "1.0"

SDL_Input* input = SDL_Input::Instance();

uint32_t frameStart;
int frameTime;
const int FPS = 60;
const int FRAME_DELAY = 1000/FPS;

bool isRunning;

SDL_Window* window;
SDL_Renderer* rend;

//for debug
MinoType typeNum = MinoType::TTYPE_I;
vector2 startPos(4,5);
TetriMino myPiece(typeNum, startPos);


//숨겨진 배경까지 해서 10x40의 행렬이 필요함.
std::vector< std::vector<bool> > Grid(10, std::vector<bool>(40));

/*
Grid.size()는 전체의 갯수, 그러니까 10을 반환
Grid[0].size()는 차원안에의 갯수, 그러니까 40을반환
*/
void grid_draw(){
    int startX = 44;
    int startY = 470;
    for(int i=0; i<Grid.size(); i++){ //가로(10)
        for(int j=0; j<Grid[0].size()/2; j++){ //세로(40)보이는건20
            if(!Grid[i][j]){
                SDL_Rect temp;
                temp.x = startX;
                temp.y = startY;
                startY -= TILE_SIZE;

                temp.w = TILE_SIZE;
                temp.h = TILE_SIZE;
                SDL_SetRenderDrawColor(rend, 0, 0, 0, 255); //검은색
                SDL_RenderFillRect(rend, &temp);
                SDL_SetRenderDrawColor(rend, 155, 155, 155, 255); //흰색
                SDL_RenderDrawRect(rend, &temp);
            }
        }
        startY = 470;
        startX+=TILE_SIZE;
    }
}

void HandleEvents(){
    SDL_Event event;
    SDL_PollEvent(&event);
    if(event.type == SDL_QUIT) isRunning = false;
    input->Update();

    if(input->KeyPressed(SDL_SCANCODE_UP)){
        std::cout << "UP" << std::endl;
        myPiece.Move_UD('U');
    }
    if(input->KeyPressed(SDL_SCANCODE_DOWN)){
        std::cout << "DOWN" << std::endl;
        myPiece.Move_UD('D');
    }
    if(input->KeyPressed(SDL_SCANCODE_LEFT)){
        std::cout << "LEFT" << std::endl;
        myPiece.Move_LR('L');
    }
    if(input->KeyPressed(SDL_SCANCODE_RIGHT)){
        std::cout << "RIGHT" << std::endl;
        myPiece.Move_LR('R');
    }
    if(input->KeyPressed(SDL_SCANCODE_X)){
        std::cout << "X" << std::endl;
        myPiece.Rotate(true);
    }
    if(input->KeyPressed(SDL_SCANCODE_Z)){
        std::cout << "Z" << std::endl;
        myPiece.Rotate(false);
    }
    if(input->KeyPressed(SDL_SCANCODE_C)){
        std::cout << "C" << std::endl;
        typeNum = static_cast<MinoType>( (typeNum + 1) % 7);
        myPiece.ChangeType(typeNum);
    }

    input->UpdatePrevInput();
}

void Update(){

}

void Render(){
    //화면 검은색으로 초기화
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
    SDL_RenderClear(rend);

    grid_draw();

    myPiece.Render(rend, TILE_SIZE);

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

    std::cout << "Grid.size() : " << Grid.size() << std::endl << "Grid[0].size() : " << Grid[0].size() << std::endl;

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
