#pragma once

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

#include "vector2.h"

class Tile{
public:
    vector2 relativePos; //센터에 대한 상대좌표
    SDL_Color color;

    Tile(int _x, int _y, SDL_Color _color) : relativePos(_x, _y), color(_color) {}

    //center기준으로 Rotation
    void RotateTile(Tile center, bool clockwise);

    void Render(SDL_Renderer* rend, int tileSize);
};