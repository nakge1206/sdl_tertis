#pragma once

#include <iostream> //디버그용 cout
#include <SDL2/SDL.h> //render
#include "vector2.h"

#define FIELD_WIDTH 10 //가로 10줄
#define FIELD_HEIGHT 20 //세로 20줄
#define TILE_SIZE 22 //타일 크기(pixel)

//게임판 생성되는 위치. (44,470)부터 시작되며, 여기가 좌표로 치면(1,1)이다.
//플레이 가능한 좌표는 (1,1) ~ (10,40)
#define STARTX 44
#define STARTY 470

enum MinoType{
    TTYPE_I, TTYPE_O, TTYPE_Z, TTYPE_S, TTYPE_J, TTYPE_L, TTYPE_T
};

struct MinoColor{
    uint8_t r, g, b, a;
};

extern MinoColor TypeColorArray[7];


struct grid
{
    vector2 gridPosition; //좌표계
    int type; //기본:-1, 굳은미노:MinoType
    bool blocked;
};


class Field{
public:
    static Field* Instance();
    void Release();
    
    void fieldDraw(SDL_Renderer* rend);
    bool isMoveAble(vector2 nextPos); //움직일 수 있으면 true 반환

    void FieldLock(vector2 lockPos, int newType);

    void FieldReset();

    //디버그용
    void setting_DT();
    void FieldPrint_blocked(){
        for(int j=41; j>=0; j--){
            for(int i=0; i<12; i++){
                std::cout << Grid[i][j].blocked << " ";
            }
            std::cout << std::endl;
        }
    }
    void FieldPrint_gridPosition(){
        for(int j=41; j>=0; j--){
            for(int i=0; i<12; i++){
                std::cout << "(" << Grid[i][j].gridPosition.x << "," << Grid[i][j].gridPosition.y << ") ";
            }
            std::cout << std::endl;
        }
    }
    void FieldPrint_type(){
        for(int j=41; j>=0; j--){
            for(int i=0; i<12; i++){
                std::cout << Grid[i][j].type << " ";
            }
            std::cout << std::endl;
        }
    }

private:
    static Field* sInstance;
    Field();
    ~Field();

    std::vector< std::vector<grid> > Grid;

};