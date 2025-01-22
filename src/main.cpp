#include "system/Window.h"

#define FIELD_WIDTH 10 //가로 10줄
#define FIELD_HEIGHT 20 //세로 20줄

#define WIDTH 960
#define HEIGHT 540
#define game_version "1.0"

int main(int argc, char* args[]){
    Window win;

    //게임화면 크기는 960x540 (qHD로 가정)
    if(!win.initSetting("SDL2 on macOS 🍎 v" game_version, WIDTH, HEIGHT)) return -1;

    win.Run();

    return 0;    
}
