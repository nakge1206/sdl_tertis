#include "Field.h"

MinoColor TypeColorArray[7] = {
    {135, 206, 235, 255}, // TTYPE_I:하늘색
    {255, 255, 0, 255},   // TTYPE_O:노랑색
    {255, 0, 0, 255},     // TTYPE_Z:빨간색
    {129, 193, 71, 255},  // TTYPE_S:연두색
    {65, 105, 225, 255},  // TTYPE_J:파란색
    {255, 127, 0, 255},  // TTYPE_L:주황색
    {204, 102, 255, 255}   // TTYPE_T:보라색
};


Field* Field::sInstance = NULL;

Field* Field::Instance(){
    if(sInstance == NULL){
        sInstance = new Field();
    }
    return sInstance;
}
void Field::Release(){
    delete sInstance;
    sInstance = NULL;
}

Field::Field() : Grid(12, std::vector<grid>(42)){
    FieldReset();
}
Field::~Field(){}

void Field::FieldReset(){
    for(int i=0; i<12; i++){
        for(int j=0; j<42; j++){
            Grid[i][j].gridPosition.x = i;
            Grid[i][j].gridPosition.y = j;
            Grid[i][j].type = -1;
            Grid[i][j].blocked = false;
            if(i==0 || i==11){
                Grid[i][j].blocked = 1;
                Grid[i][j].blocked = 1;
            }
            if(j==0 || j==41){
                Grid[i][j].blocked = 1;
                Grid[i][j].blocked = 1;
            }
        }
    }
}

bool Field::isMoveAble(vector2 nextPos){
    return !Grid[nextPos.x][nextPos.y].blocked;
}

void Field::FieldLock(vector2 lockPos, int newType){
    Grid[lockPos.x][lockPos.y].blocked = true;
    Grid[lockPos.x][lockPos.y].type = newType;
}

void Field::fieldDraw(SDL_Renderer* rend){
    int X = STARTX;
    int Y = STARTY;
    //출력되는거는 실제로 게임이 돌아가는 (1,1)~(10,20)
    for(int i=1; i<11; i++){
        for(int j=1; j<21; j++){
            SDL_Rect temp;
            temp.x = X;
            temp.y = Y;
            Y -= TILE_SIZE;

            temp.w = TILE_SIZE;
            temp.h = TILE_SIZE;
            //type에 따라 칠해지는 색깔이 달라짐
            if(Grid[i][j].type == -1){
                SDL_SetRenderDrawColor(rend, 0, 0, 0, 255); //검은색
                SDL_RenderFillRect(rend, &temp);
                SDL_SetRenderDrawColor(rend, 155, 155, 155, 255); //흰색
                SDL_RenderDrawRect(rend, &temp);
            }else{
                switch (static_cast<MinoType>(Grid[i][j].type)){
                case TTYPE_I:
                    SDL_SetRenderDrawColor(rend, TypeColorArray[TTYPE_I].r, TypeColorArray[TTYPE_I].g, TypeColorArray[TTYPE_I].b, TypeColorArray[TTYPE_I].a);
                    SDL_RenderFillRect(rend, &temp);
                    SDL_SetRenderDrawColor(rend, 219, 219, 219, 255);
                    SDL_RenderDrawRect(rend, &temp);
                    break;
                case TTYPE_O:
                    SDL_SetRenderDrawColor(rend, TypeColorArray[TTYPE_O].r, TypeColorArray[TTYPE_O].g, TypeColorArray[TTYPE_O].b, TypeColorArray[TTYPE_O].a);
                    SDL_RenderFillRect(rend, &temp);
                    SDL_SetRenderDrawColor(rend, 219, 219, 219, 255);
                    SDL_RenderDrawRect(rend, &temp);
                    break;
                case TTYPE_Z:
                    SDL_SetRenderDrawColor(rend, TypeColorArray[TTYPE_Z].r, TypeColorArray[TTYPE_Z].g, TypeColorArray[TTYPE_Z].b, TypeColorArray[TTYPE_Z].a);
                    SDL_RenderFillRect(rend, &temp);
                    SDL_SetRenderDrawColor(rend, 219, 219, 219, 255);
                    SDL_RenderDrawRect(rend, &temp);
                    break;
                case TTYPE_S:
                    SDL_SetRenderDrawColor(rend, TypeColorArray[TTYPE_S].r, TypeColorArray[TTYPE_S].g, TypeColorArray[TTYPE_S].b, TypeColorArray[TTYPE_S].a);
                    SDL_RenderFillRect(rend, &temp);
                    SDL_SetRenderDrawColor(rend, 219, 219, 219, 255);
                    SDL_RenderDrawRect(rend, &temp);
                    break;
                case TTYPE_J:
                    SDL_SetRenderDrawColor(rend, TypeColorArray[TTYPE_J].r, TypeColorArray[TTYPE_J].g, TypeColorArray[TTYPE_J].b, TypeColorArray[TTYPE_J].a);
                    SDL_RenderFillRect(rend, &temp);
                    SDL_SetRenderDrawColor(rend, 219, 219, 219, 255);
                    SDL_RenderDrawRect(rend, &temp);
                    break;
                case TTYPE_L:
                    SDL_SetRenderDrawColor(rend, TypeColorArray[TTYPE_L].r, TypeColorArray[TTYPE_L].g, TypeColorArray[TTYPE_L].b, TypeColorArray[TTYPE_L].a);
                    SDL_RenderFillRect(rend, &temp);
                    SDL_SetRenderDrawColor(rend, 219, 219, 219, 255);
                    SDL_RenderDrawRect(rend, &temp);
                    break;
                case TTYPE_T:
                    SDL_SetRenderDrawColor(rend, TypeColorArray[TTYPE_T].r, TypeColorArray[TTYPE_T].g, TypeColorArray[TTYPE_T].b, TypeColorArray[TTYPE_T].a);
                    SDL_RenderFillRect(rend, &temp);
                    SDL_SetRenderDrawColor(rend, 219, 219, 219, 255);
                    SDL_RenderDrawRect(rend, &temp);
                    break;
                }
            }
            
        }
        Y = STARTY;
        X+=TILE_SIZE;
    }
}


//디버그용
void Field::setting_DT(){
    Grid[1][1].type=TTYPE_O;
    Grid[1][1].blocked = true;
    Grid[2][1].type=TTYPE_O;
    Grid[2][1].blocked = true;
    Grid[1][2].type=TTYPE_O;
    Grid[1][2].blocked = true;
    Grid[2][2].type=TTYPE_O;
    Grid[2][2].blocked = true;

    Grid[4][1].type=TTYPE_L;
    Grid[4][1].blocked = true;
    Grid[5][1].type=TTYPE_L;
    Grid[5][1].blocked = true;
    Grid[6][1].type=TTYPE_L;
    Grid[6][1].blocked = true;
    Grid[6][2].type=TTYPE_L;
    Grid[6][2].blocked = true;

    Grid[7][1].type=TTYPE_I;
    Grid[7][1].blocked = true;
    Grid[7][2].type=TTYPE_I;
    Grid[7][2].blocked = true;
    Grid[7][3].type=TTYPE_I;
    Grid[7][3].blocked = true;
    Grid[7][4].type=TTYPE_I;
    Grid[7][4].blocked = true;

    Grid[8][1].type=TTYPE_J;
    Grid[8][1].blocked = true;
    Grid[8][2].type=TTYPE_J;
    Grid[8][2].blocked = true;
    Grid[9][1].type=TTYPE_J;
    Grid[9][1].blocked = true;
    Grid[10][1].type=TTYPE_J;
    Grid[10][1].blocked = true;

    Grid[1][3].type=TTYPE_J;
    Grid[1][3].blocked = true;
    Grid[1][4].type=TTYPE_J;
    Grid[1][4].blocked = true;
    Grid[1][5].type=TTYPE_J;
    Grid[1][5].blocked = true;
    Grid[2][5].type=TTYPE_J;
    Grid[2][5].blocked = true;

    Grid[4][2].type=TTYPE_S;
    Grid[4][2].blocked = true;
    Grid[5][2].type=TTYPE_S;
    Grid[5][2].blocked = true;
    Grid[5][3].type=TTYPE_S;
    Grid[5][3].blocked = true;
    Grid[6][3].type=TTYPE_S;
    Grid[6][3].blocked = true;

    Grid[4][4].type=TTYPE_T;
    Grid[4][4].blocked = true;
    Grid[5][4].type=TTYPE_T;
    Grid[5][4].blocked = true;
    Grid[6][4].type=TTYPE_T;
    Grid[6][4].blocked = true;
    Grid[5][5].type=TTYPE_T;
    Grid[5][5].blocked = true;

    Grid[4][5].type=TTYPE_L;
    Grid[4][5].blocked = true;
    Grid[4][6].type=TTYPE_L;
    Grid[4][6].blocked = true;
    Grid[4][7].type=TTYPE_L;
    Grid[4][7].blocked = true;
    Grid[3][7].type=TTYPE_L;
    Grid[3][7].blocked = true;
}