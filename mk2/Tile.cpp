#include "Tile.h"

//center기준으로 Rotation
void Tile::RotateTile(Tile center, bool clockwise){
    int relativeX = relativePos.x;
    int relativeY = relativePos.y;

    vector2 rotMatrix[2];
    if (clockwise) { // 시계 방향
        rotMatrix[0] = vector2(0,-1);
        rotMatrix[1] = vector2(1,0);
    } else { // 반시계 방향
        rotMatrix[0] = vector2(0,1);
        rotMatrix[1] = vector2(-1,0);
    }
    int newXPos = (rotMatrix[0].x * relativeX) + (rotMatrix[1].x * relativeY);
    int newYPos = (rotMatrix[0].y * relativeX) + (rotMatrix[1].y * relativeY);
    vector2 newPos(newXPos, newYPos);

    relativePos.x = newPos.x;
    relativePos.y = newPos.y;
}

void Tile::Render(SDL_Renderer* rend, int tileSize){
    SDL_Rect rect = {relativePos.x, relativePos.y, tileSize, tileSize};
    SDL_SetRenderDrawColor(rend, color.r, color.g, color.b, 255);
    SDL_RenderFillRect(rend, &rect);
    SDL_SetRenderDrawColor(rend, 219, 219, 219, 255);
    SDL_RenderDrawRect(rend, &rect);
}