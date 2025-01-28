#pragma once

#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <vector>
#include "../sdl/CreateButton.h"
#include "../sdl/SDL_font.h"
#include "../sdl/SDL_Input.h"

class game{
public:

private:
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

    shape block[7]{
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
        , 5, 4, 3}}


    }
    
private:
    game();
    ~game();
};