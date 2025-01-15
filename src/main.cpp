#include "definitions.h"
#include "system/Window.h"

#define FIELD_WIDTH 10 //가로 10줄
#define FIELD_HEIGHT 20 //세로 20줄

int main(int argc, char* args[]){
    Window win;

    if(!win.initSetting("SDL2 on macOS 🍎 v" game_version, 640, 480)) return -1;

    win.Run();
    win.Shutdown();

    return 0;    
}
