#include "Window.h"
#include <functional>

const int FPS = 60;
const int FRAME_DELAY = 1000/FPS;

#define LOGICAL_WIDTH 960
#define LOGICAL_HEIGHT 540


Window::Window(){
    window = nullptr; rend = nullptr;
    isRunning = false;
    frameStart = 0; frameTime = 0;
    currentState = MAIN; isPause = false;
    input = SDL_Input::Instance();
}

Window::~Window(){
    SDL_Input::Release();
    input = NULL;

    Shutdown();
}

bool Window::initSetting(const char* title, int width, int height){
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_GAMECONTROLLER|SDL_INIT_EVENTS) != 0) { //비디오, 타이머, 컨트롤러 설정
        std::cerr << "SDL 초기설정 실패: " << SDL_GetError() << std::endl;
        return false;
    }
    if(TTF_Init() == -1){
        std::cerr << "폰트설정 실패: " <<SDL_GetError() << std::endl;
    }

    window = SDL_CreateWindow( //윈도우 생성
                        title , //윈도우 이름
                        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, //초기 마우스 위치
                        width, height, //창 크기
                        SDL_WINDOW_RESIZABLE); //속성(다중 가능)
    if(!window){
        std::cerr << "윈도우 생성 실패" << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }
    rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC); //랜더러 설정
    if (!rend) {
        std::cerr << "랜더러 생성 실패" << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }
    SDL_RenderSetLogicalSize(rend, LOGICAL_WIDTH, LOGICAL_HEIGHT);

    //메뉴창 설정 수정필요
    mainMenu = MainMenu();
    mainMenu.initMain(rend, window);

    isRunning = true;
    return true;

}

void Window::Run(){
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
}

void Window::HandleEvents(){
    SDL_Event event;
    SDL_PollEvent(&event);
    if(event.type == SDL_QUIT) isRunning = false;
    if(mainMenu.isQuit == true) isRunning = false;

    input->Update();

    if(input->KeyPressed(SDL_SCANCODE_DOWN)) printf("DOWN is click \n");

    if(currentState == MAIN){
        if(input->KeyPressed(SDL_SCANCODE_LEFT)) printf("LEFT is click \n");
        if(input->MouseButtonPressed(SDL_Input::left)){
            mainMenu.OnClick();
        }
        if(input->KeyPressed(SDL_SCANCODE_UP)){
            mainMenu.UpClick();
        }
        if(input->KeyPressed(SDL_SCANCODE_DOWN)){
            mainMenu.DownClick();
        }
        if(input->KeyPressed(SDL_SCANCODE_RETURN)){
            mainMenu.EnterClick();
        }
    }

    if(currentState == GAME){
        if(input->KeyPressed(SDL_SCANCODE_L)){
            printf("L is click\n");
            currentState = MAIN;
        }
    }
    

    input->UpdatePrevInput();
}

void Window::Update(){
    //게임 상태 업데이트 코드 추가.
    switch (currentState) {
        case MAIN:
            if(mainMenu.mainStart) {
                printf("gamemode change main->game\n");
                currentState = GAME;
            }
            if(mainMenu.mainSetting) printf("gamemode change main->setting\n");
            // 메뉴 상태 업데이트 처리
            break;
        case GAME:
            // 게임 상태 업데이트 처리
            break;
        case SETTINGS:
            // 설정 상태 업데이트 처리
            break;
        case QUIT:
            isRunning = false;
            break;
    }
}

void Window::Render(){
   //화면 검은색으로 초기화
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
    SDL_RenderClear(rend);

    //상태에 따라 화면 출력 처리
    switch (currentState) {
        case MAIN: {
            mainMenu.mainSetting=false; mainMenu.mainStart=false;
            mainMenu.render();
            break;
        }
        case GAME: {
            //나중에 게임 시작 함수 추가해야함.

            //디버그:초록색
            SDL_SetRenderDrawColor(rend, 0, 255, 0, 255);
            SDL_Rect gameRect = {150, 150, 300, 200};
            SDL_RenderFillRect(rend, &gameRect);
            break;
        }
        case SETTINGS: {
            //menus.setMenu(menus.callType(2));
            //디버그:노란색
            // SDL_SetRenderDrawColor(rend, 255, 255, 0, 255);
            // SDL_Rect settingsRect = {200, 200, 200, 100};
            // SDL_RenderFillRect(rend, &settingsRect);
            break;
        }
        case QUIT:
            break;
    }

    // 결과 화면에 출력
    SDL_RenderPresent(rend);
}

void Window::Shutdown(){
    if(window){
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    if(rend){
        SDL_DestroyRenderer(rend);
        rend = nullptr;
    }
    TTF_Quit();
    SDL_Quit();
}