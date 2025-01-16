#include "Window.h"
#include <functional>

const int FPS = 60;
const int FRAME_DELAY = 1000/FPS;

Window::Window()
    : window(nullptr), rend(nullptr), isRunning(false), frameStart(0), frameTime(0), currentState(MAIN_MENU), menus(nullptr, nullptr), isWindowResized(false){
}

Window::~Window(){
    Shutdown();
}

bool Window::initSetting(const char* title, int width, int height){
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_GAMECONTROLLER) != 0) { //비디오, 타이머, 컨트롤러 설정
        std::cerr << "SDL 초기설정 실패: " << SDL_GetError() << std::endl;
        return false;
    }
    //이건 나중에 SDL_font로 따로 빼고싶음.
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
    menus = TotalMenu(rend, window);
    //initMainMenu에서 세그멘테이션 오류뜸.
    menus.initMainMenu();
    //menus.initPauseMenu();
    //menus.initSettingMenu();

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
    while(SDL_PollEvent(&event)){
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }
        if(event.type == SDL_WINDOWEVENT){
            if(event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED){
                isWindowResized = true;
            }
        }
    }
}

void Window::Update(){
    //게임 상태 업데이트 코드 추가.
    switch (currentState) {
        case MAIN_MENU:
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
        case MAIN_MENU: {
            menus.setMenu(menus.callType(0));
            menus.render();
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