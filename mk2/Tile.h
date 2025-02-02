#pragma once

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

#include "vector2.h"

class Tile{
public:
    Vector2Int position;
    SDL_Color color;
    //bool activate;

    Tile(int _x, int _y, SDL_Color _color) : position(_x, _y), color(_color) {}

    void RotateTile(Tile center, bool clockwise){
        int relativeX = position.x - center.position.x;
        int relativeY = position.y - center.position.y;

        Vector2Int rotMatrix[2];
        if (clockwise) { // 시계 방향
            rotMatrix[0] = Vector2Int(0,-1);
            rotMatrix[1] = Vector2Int(1,0);
        } else { // 반시계 방향
            rotMatrix[0] = Vector2Int(0,1);
            rotMatrix[1] = Vector2Int(-1,0);
        }
        int newXPos = (rotMatrix[0].x * relativeX) + (rotMatrix[1].x * relativeY);
        int newYPos = (rotMatrix[0].y * relativeX) + (rotMatrix[1].y * relativeY);
        Vector2Int newPos(newXPos, newYPos);

        position.x = newPos.x + center.position.x;
        position.y = newPos.y + center.position.y;
    }

    void Render(SDL_Renderer* rend, int tileSize) {
        SDL_Rect rect = {position.x, position.y, tileSize, tileSize};
        SDL_SetRenderDrawColor(rend, color.r, color.g, color.b, 255); // 색상 채우기
        SDL_RenderFillRect(rend, &rect);
        SDL_SetRenderDrawColor(rend, 219, 219, 219, 255);
        SDL_RenderDrawRect(rend, &rect);
    }
};