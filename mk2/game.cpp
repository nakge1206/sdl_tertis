#include "game.h"

game::game():GameRunning(false){
    input = SDL_Input::Instance();
    playField = Field::Instance();
    gravitySum = 0.0;
    fallInterval = 1000.0;
    lockDelay = 500;

    //디버그
    vector2 createPos(5,21);
    tempBag.push_back(TetroMino(TTYPE_I, createPos));
    tempBag.push_back(TetroMino(TTYPE_J, createPos));
    tempBag.push_back(TetroMino(TTYPE_L, createPos));
    tempBag.push_back(TetroMino(TTYPE_O, createPos));
    tempBag.push_back(TetroMino(TTYPE_S, createPos));
    tempBag.push_back(TetroMino(TTYPE_T, createPos));
    tempBag.push_back(TetroMino(TTYPE_Z, createPos));
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
            tempBag[bagNum].Move('D');
            //todo: lock부분 고쳐야함
            if(!tempBag[bagNum].WillMove('D')){
                tempBag[bagNum].lock();
            }

            gravitySum = 0;
            downTimer.reset();
        }
    }
}

void game::handleEvent(){
    if(input->KeyPressed(SDL_SCANCODE_UP)){
        std::cout << "UP" << std::endl;
        // tempBag[bagNum].Move_UD('U');
    }
    if(input->KeyPressed(SDL_SCANCODE_DOWN)){
        std::cout << "DOWN" << std::endl;
        // tempBag[bagNum].Move_UD('D');
    }
    if(input->KeyPressed(SDL_SCANCODE_LEFT)){
        std::cout << "LEFT" << std::endl;
        tempBag[bagNum].Move('L');
    }
    if(input->KeyPressed(SDL_SCANCODE_RIGHT)){
        std::cout << "RIGHT" << std::endl;
        tempBag[bagNum].Move('R');
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
        bagNum++; if(bagNum == 7) bagNum = 0;
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

void game::render(SDL_Renderer* rend){
    playField->fieldDraw(rend);
    tempBag[bagNum].Render(rend);
}

bool game::isGameRunning(){
    return GameRunning;
}