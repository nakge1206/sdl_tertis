#include "game.h"

game::game():GameRunning(false){
    input = SDL_Input::Instance();
    playField = Field::Instance();
    //gravity
    gravitySum = 0.0;
    fallInterval = 1000.0;
    //lock
    lockDelay = 800;
    //DAS
    DAS_Delay = 200;
    DAS_DOWN = false;
    DAS_LEFT = false;
    DAS_RIGHT = false;

    //디버그
    //todo: 7-bag 구현
    resetBag();
    bagNum = 0;
}
game::~game(){
    playField->Release();

    input = NULL;
    playField = NULL;
}

void game::start(){
    GameRunning = true;
    downTimer.start();
}

void game::tick(){
    int elapsed = downTimer.getTicks();

    if(GameRunning){
        //todo: 나중에 레벨시스템 구현하고 하드코딩 수정해야함.
        int Level = 1;
        double speed = 1 * Level;
        gravitySum += speed * elapsed;
        if(gravitySum >= fallInterval){
            if(!tempBag[bagNum].WillMove('D')){
                if(lockDelayTimer.isStart()){
                    if(lockDelayTimer.getTicks()>=lockDelay){
                        tempBag[bagNum].lock();
                    }
                }else {
                    lockDelayTimer.start();
                }
            }
            tempBag[bagNum].Move('D');

            gravitySum = 0;
            downTimer.reset();
        }
    }
}

void game::handleEvent(){
    if(input->KeyPressed(SDL_SCANCODE_UP)){
        std::cout << "UP" << std::endl;
        tempBag[bagNum].Rotate(true);
    }
    if(input->KeyPressed(SDL_SCANCODE_DOWN)){
        if(!DAS_DOWN){
            DAS_DOWN=true;
            DAS_Timer.start();
            lockDelayTimer.reset();
            tempBag[bagNum].Move('D');
        }
    }
    if(input->KeyReleased(SDL_SCANCODE_DOWN)){
        if(DAS_DOWN){
            DAS_DOWN=false;
        }
    }
    if(input->KeyPressed(SDL_SCANCODE_LEFT)){
        if(!DAS_LEFT){
            DAS_LEFT=true;
            DAS_Timer.start();
            lockDelayTimer.reset();
            tempBag[bagNum].Move('L');
        }
    }
    if(input->KeyReleased(SDL_SCANCODE_LEFT)){
        if(DAS_LEFT){
            DAS_LEFT=false;
        }
    }

    if(input->KeyPressed(SDL_SCANCODE_RIGHT)){
        if(!DAS_RIGHT){
            DAS_RIGHT=true;
            DAS_Timer.start();
            lockDelayTimer.reset();
            tempBag[bagNum].Move('R');
        }
    }
    if(input->KeyReleased(SDL_SCANCODE_RIGHT)){
        if(DAS_RIGHT){
            DAS_RIGHT=false;
        }
    }

    if(input->KeyPressed(SDL_SCANCODE_X)){
        std::cout << "X" << std::endl;
        tempBag[bagNum].Rotate(true);
    }
    if(input->KeyPressed(SDL_SCANCODE_Z)){
        std::cout << "Z" << std::endl;
        tempBag[bagNum].Rotate(false);
    }
    if(input->KeyPressed(SDL_SCANCODE_C)){
        std::cout << "C" << std::endl;
        //현재는 미노만 변경하고 있음
        //todo: Hold구현
        bagNum++; if(bagNum == 7){
            bagNum = 0;
            resetBag();
        }
    }

    if(input->KeyPressed(SDL_SCANCODE_ESCAPE)){
        std::cout << "esc" << std::endl;
        GameRunning = false;
    }
    
    if(input->KeyPressed(SDL_SCANCODE_L)){
        playField->setting_DT();
    }
    if(input->KeyPressed(SDL_SCANCODE_K)){
        playField->FieldReset();
    }
    if(input->KeyPressed(SDL_SCANCODE_I)){
        std::cout << "I Grid_type print" << std::endl;
        playField->FieldPrint_type();
    }
    if(input->KeyPressed(SDL_SCANCODE_O)){
        std::cout << "O Grid_position print" << std::endl;
        playField->FieldPrint_gridPosition();
    }
    if(input->KeyPressed(SDL_SCANCODE_P)){
        std::cout << "P Grid_blocked print" << std::endl;
        playField->FieldPrint_blocked();
    }
}

void game::moveUpdate(){
    if(DAS_RIGHT){
        if(DAS_Timer.getTicks() >= DAS_Delay){
            tempBag[bagNum].Move('R');
            DAS_Timer.reset();
            lockDelayTimer.reset();
        }
    }
    if(DAS_LEFT){
        if(DAS_Timer.getTicks() >= DAS_Delay){
            tempBag[bagNum].Move('L');
            DAS_Timer.reset();
            lockDelayTimer.reset();
        }
    }
    if(DAS_DOWN){
        if(DAS_Timer.getTicks() >= DAS_Delay){
            tempBag[bagNum].Move('D');
            DAS_Timer.reset();
            lockDelayTimer.reset();
        }
    }
}

void game::render(SDL_Renderer* rend){
    playField->fieldDraw(rend);
    tempBag[bagNum].Render(rend);
}

bool game::isGameRunning(){
    return GameRunning;
}

//디버그용
void game::resetBag(){
    vector2 createPos(5,21);
    tempBag.clear();
    tempBag.push_back(TetroMino(TTYPE_I, createPos));
    tempBag.push_back(TetroMino(TTYPE_J, createPos));
    tempBag.push_back(TetroMino(TTYPE_L, createPos));
    tempBag.push_back(TetroMino(TTYPE_O, createPos));
    tempBag.push_back(TetroMino(TTYPE_S, createPos));
    tempBag.push_back(TetroMino(TTYPE_T, createPos));
    tempBag.push_back(TetroMino(TTYPE_Z, createPos));
}  