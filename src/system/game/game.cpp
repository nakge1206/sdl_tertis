#include <SDL2/SDL.h>
#include <vector>
#include <iostream>


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

shape blocks[7] = {
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
    , 5, 4, 3}}, cur;

shape reverseCols(shape s){
    shape tmp = s;
    for(int i=0; i<s.size; i++){
        for(int j=0; i<s.size/2; j++){
            bool t = s.matrix[i][j];
            tmp.matrix[i][j] = s.matrix[i][s.size-j-i];
            tmp.matrix[i][s.size-j-1] = t;
        }
    }
    return tmp;
}

shape transepose(shape s) {
    shape tmp = s;
    for(int i=0; i<s.size; i++){
        for(int j=0; i<s.size; j++){
            tmp.matrix[i][j] = s.matrix[j][i];
        }
    }
    return tmp;
}

void rotate(){
    cur = reverseCols(transepose(cur));
}

void draw(shape s){
    for(int i=0; i<s.size; i++){
        for(int j=0; j<s.size, j++){
            if(s.matrix[i][j]){
                rect.x = (s.x+i)*TITLE_SIZE; (rect.y+j)*TITLE_SIZE;
                SDL_SetRenderDrawColor(renderer, s.color.r, s.color.g, s.color.b, 255);
                SDL_RenderFillRect(renderer, &rect);
                SDL_SetRenderDrawColor(renderer, 219, 219, 219, 255);
                SDL_RenderDrawRect(renderer, &rect);
            }
        }
    }
}

srand(time(NULL));
cur = blocks[rand()%7];
