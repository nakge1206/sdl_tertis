#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

#include "Tile.h"
#include "vector2.h"


class Piece {
public:
    std::vector<Tile> tiles;
    int type; // 블록 종류 (0: I, 1: J, 2: L, 3: O, 4: S, 5: T, 6: Z)
    int rotation; // 현재 회전 상태 (0, 1, 2, 3)
    Vector2Int position; // 블록의 좌표 (좌상단 타일 기준)

    Piece(int _type, Vector2Int _position = Vector2Int()) : type(_type), rotation(0), position(_position) {
        Awake();
        // 블록 종류에 따라 타일 초기화
        switch (type) {
            case 0: // I
            {
                SDL_Color Icolor = {253, 255, 255, 255};
                tiles.push_back(Tile(0, 0, Icolor));
                tiles.push_back(Tile(-1, 0, Icolor));
                tiles.push_back(Tile(1, 0, Icolor));
                tiles.push_back(Tile(2, 0, Icolor));
                break;
            }
            case 1: // J
            {
                SDL_Color Jcolor = {0, 0, 255, 255};
                tiles.push_back(Tile(0, 0, Jcolor));
                tiles.push_back(Tile(-1, 0, Jcolor));
                tiles.push_back(Tile(-1, 1, Jcolor));
                tiles.push_back(Tile(1, 0, Jcolor));
                break;
            }
            case 2: // L
            {
                SDL_Color Lcolor = {255, 165, 0, 255};
                tiles.push_back(Tile(0, 0, Lcolor));
                tiles.push_back(Tile(-1, 0, Lcolor));
                tiles.push_back(Tile(1, 0, Lcolor));
                tiles.push_back(Tile(1, 1, Lcolor));
                break;
            }
            case 3: // O
            {
                SDL_Color Ocolor = {255, 255, 0, 255};
                tiles.push_back(Tile(0, 0, Ocolor));
                tiles.push_back(Tile(1, 0, Ocolor));
                tiles.push_back(Tile(0, 1, Ocolor));
                tiles.push_back(Tile(1, 1, Ocolor));
                break;
            }
            case 4: // S
            {
                SDL_Color Scolor = {0, 0, 255, 255};
                tiles.push_back(Tile(0, 0, Scolor));
                tiles.push_back(Tile(-1, 0, Scolor));
                tiles.push_back(Tile(0, 1, Scolor));
                tiles.push_back(Tile(1, 1, Scolor));
                break;
            }
            case 5: // T
            {
                SDL_Color Tcolor = {128, 0, 128, 255};
                tiles.push_back(Tile(0, 0, Tcolor));
                tiles.push_back(Tile(-1, 0, Tcolor));
                tiles.push_back(Tile(0, 1, Tcolor));
                tiles.push_back(Tile(1, 0, Tcolor));
                break;
            }
            case 6: // Z
            {
                SDL_Color Zcolor = {255, 0, 0, 255};
                tiles.push_back(Tile(0, 0, Zcolor));
                tiles.push_back(Tile(1, 0, Zcolor));
                tiles.push_back(Tile(0, 1, Zcolor));
                tiles.push_back(Tile(-1, 1, Zcolor));
                break;
            }
        }
    }

    void ChangeType(int newType) {
        type = newType; // 블록 종류 변경
        tiles.clear(); // 기존 타일 정보 초기화

        // 새로운 블록 종류에 따라 타일 정보 다시 생성
        switch (type) {
            case 0: // I
            {
                SDL_Color Icolor = {253, 255, 255, 255};
                tiles.push_back(Tile(0, 0, Icolor));
                tiles.push_back(Tile(-1, 0, Icolor));
                tiles.push_back(Tile(1, 0, Icolor));
                tiles.push_back(Tile(2, 0, Icolor));
                break;
            }
            case 1: // J
            {
                SDL_Color Jcolor = {0, 0, 255, 255};
                tiles.push_back(Tile(0, 0, Jcolor));
                tiles.push_back(Tile(-1, 0, Jcolor));
                tiles.push_back(Tile(-1, 1, Jcolor));
                tiles.push_back(Tile(1, 0, Jcolor));
                break;
            }
            case 2: // L
            {
                SDL_Color Lcolor = {255, 165, 0, 255};
                tiles.push_back(Tile(0, 0, Lcolor));
                tiles.push_back(Tile(-1, 0, Lcolor));
                tiles.push_back(Tile(1, 0, Lcolor));
                tiles.push_back(Tile(1, 1, Lcolor));
                break;
            }
            case 3: // O
            {
                SDL_Color Ocolor = {255, 255, 0, 255};
                tiles.push_back(Tile(0, 0, Ocolor));
                tiles.push_back(Tile(1, 0, Ocolor));
                tiles.push_back(Tile(0, 1, Ocolor));
                tiles.push_back(Tile(1, 1, Ocolor));
                break;
            }
            case 4: // S
            {
                SDL_Color Scolor = {0, 0, 255, 255};
                tiles.push_back(Tile(0, 0, Scolor));
                tiles.push_back(Tile(-1, 0, Scolor));
                tiles.push_back(Tile(0, 1, Scolor));
                tiles.push_back(Tile(1, 1, Scolor));
                break;
            }
            case 5: // T
            {
                SDL_Color Tcolor = {128, 0, 128, 255};
                tiles.push_back(Tile(0, 0, Tcolor));
                tiles.push_back(Tile(-1, 0, Tcolor));
                tiles.push_back(Tile(0, 1, Tcolor));
                tiles.push_back(Tile(1, 0, Tcolor));
                break;
            }
            case 6: // Z
            {
                SDL_Color Zcolor = {255, 0, 0, 255};
                tiles.push_back(Tile(0, 0, Zcolor));
                tiles.push_back(Tile(1, 0, Zcolor));
                tiles.push_back(Tile(0, 1, Zcolor));
                tiles.push_back(Tile(-1, 1, Zcolor));
                break;
            }
        }
    }

    void Rotate(bool clockwise, bool shouldOffset = true) {
        if(type == 3) return;
        int oldRotationIndex = rotation;
        rotation += clockwise ? 1 : -1;
        rotation = Mod(rotation, 4);
        
        // 회전 중심 타일 (블록 위치 기준)
        Tile center = tiles[0];

        // 모든 타일을 회전
        for (Tile& tile : tiles) {
            tile.RotateTile(center, clockwise);
        }

        if(!shouldOffset) return;

        bool canOffset = Offset(oldRotationIndex, rotation);

        if(!canOffset){
            Rotate(!clockwise, false);
            std::cout << "Rotate(!clockwise, false) Yab!" << std::endl;
        }
        
    }


    void Move(char m){
        // 1. 이동 가능 여부 확인
        if (WillMove(m)) {
            // 2. 이동 가능할 경우 블록 실제 이동
            if(m=='L'){ //Left
                position.x--;
            }else if(m=='R'){ //Right
                position.x++;
            }
        }
    }

    void Render(SDL_Renderer* renderer, int tileSize) {
        for (Tile& tile : tiles) {
            int startX = 44;
            int startY = 470;
            Tile tileToDraw = tile;
            tileToDraw.position.x = startX + (position.x * tileSize) + (tile.position.x * tileSize);
            tileToDraw.position.y = startY - (position.y * tileSize) - (tile.position.y * tileSize);

            tileToDraw.Render(renderer, tileSize);
        }
    }

private:

    std::vector< std::vector<Vector2Int> > JLSTZ_OFFSET_DATA;
    std::vector< std::vector<Vector2Int> > I_OFFSET_DATA;
    std::vector< std::vector<Vector2Int> > O_OFFSET_DATA;

    bool Offset(int oldRotIndex, int newRotIndex) {
        Vector2Int offsetVal1, offsetVal2, endOffset;

        // 블록 종류에 따라 오프셋 데이터 선택
        std::vector<std::vector<Vector2Int> > curOffsetData;
        if (type == 0) curOffsetData = I_OFFSET_DATA; // I
        else if (type == 3) curOffsetData = O_OFFSET_DATA; // O
        else curOffsetData = JLSTZ_OFFSET_DATA; //JLSTZ

        endOffset = Vector2Int(0, 0);

        bool movePossible=false;

        for (int testIndex = 0; testIndex < 5; testIndex++) {
            offsetVal1 = curOffsetData[testIndex][oldRotIndex];
            offsetVal2 = curOffsetData[testIndex][newRotIndex];
            endOffset.x = offsetVal1.x - offsetVal2.x;
            endOffset.y = offsetVal1.y - offsetVal2.y;

            if (CanMovePiece(endOffset)) {
                movePossible = true;
                break;
            }
        }

        if (movePossible) {
            MovePiece(endOffset);
        }

        return movePossible;
    }

    bool CanMovePiece(Vector2Int offset) {
        std::cout<<"들어는 옴?" << std::endl;
        std::vector<Tile> nextTiles = tiles;
        // for (Tile& tile : nextTiles) {
        //     tile.position.x += position.x + offset.x;
        //     tile.position.y += position.y + offset.y;
        // }

        for (const Tile& tile : nextTiles) {
            if (position.x + tile.position.x < 0 ||position.x + tile.position.x >= 10 ||position.y+ tile.position.y < 0) {
                std::cout<<"이상한데서 막히는건 아니겠지?" << std::endl;
                return false;
            }
        }

        return true;
    }

    void MovePiece(Vector2Int offset) {
        position.x += offset.x;
        position.y += offset.y;
    }

    int Mod(int x, int m){
        return (x % m + m) % m;
    }

    bool WillMove(char m){
        Vector2Int nextPosition = position;
        if(m=='L'){
            nextPosition.x--;
        }else if(m=='R'){
            nextPosition.x++;
        }

        std::vector<Tile> currentTiles = tiles; 
        for (Tile& tile : currentTiles) {
            tile.position.x += nextPosition.x;
            tile.position.y += nextPosition.y;
        }

        for (const Tile& tile : currentTiles) {
            if (tile.position.x < 0 || tile.position.x >= 10 || tile.position.y < 0) {
                return false;
            }
        }

        return true;
    }

    void Awake() {

        // JLSTZ 블록 오프셋 데이터
        for (int i = 0; i < 5; ++i) {
            JLSTZ_OFFSET_DATA.push_back(std::vector<Vector2Int>(4)); // 각 행(벡터) 생성
        }
        JLSTZ_OFFSET_DATA[0][0].x = 0;
        JLSTZ_OFFSET_DATA[0][0].y = 0;
        JLSTZ_OFFSET_DATA[0][1].x = 0;
        JLSTZ_OFFSET_DATA[0][1].y = 0;
        JLSTZ_OFFSET_DATA[0][2].x = 0;
        JLSTZ_OFFSET_DATA[0][2].y = 0;
        JLSTZ_OFFSET_DATA[0][3].x = 0;
        JLSTZ_OFFSET_DATA[0][3].y = 0;

        JLSTZ_OFFSET_DATA[1][0].x = 0;
        JLSTZ_OFFSET_DATA[1][0].y = 0;
        JLSTZ_OFFSET_DATA[1][1].x = 1;
        JLSTZ_OFFSET_DATA[1][1].y = 0;
        JLSTZ_OFFSET_DATA[1][2].x = 0;
        JLSTZ_OFFSET_DATA[1][2].y = 0;
        JLSTZ_OFFSET_DATA[1][3].x = -1;
        JLSTZ_OFFSET_DATA[1][3].y = 0;

        JLSTZ_OFFSET_DATA[2][0].x = 0;
        JLSTZ_OFFSET_DATA[2][0].y = 0;
        JLSTZ_OFFSET_DATA[2][1].x = 1;
        JLSTZ_OFFSET_DATA[2][1].y = -1;
        JLSTZ_OFFSET_DATA[2][2].x = 0;
        JLSTZ_OFFSET_DATA[2][2].y = 0;
        JLSTZ_OFFSET_DATA[2][3].x = -1;
        JLSTZ_OFFSET_DATA[2][3].y = 1;

        JLSTZ_OFFSET_DATA[3][0].x = 0;
        JLSTZ_OFFSET_DATA[3][0].y = 0;
        JLSTZ_OFFSET_DATA[3][1].x = 0;
        JLSTZ_OFFSET_DATA[3][1].y = 2;
        JLSTZ_OFFSET_DATA[3][2].x = 0;
        JLSTZ_OFFSET_DATA[3][2].y = 0;
        JLSTZ_OFFSET_DATA[3][3].x = 0;
        JLSTZ_OFFSET_DATA[3][3].y = 2;

        JLSTZ_OFFSET_DATA[4][0].x = 0;
        JLSTZ_OFFSET_DATA[4][0].y = 0;
        JLSTZ_OFFSET_DATA[4][1].x = 1;
        JLSTZ_OFFSET_DATA[4][1].y = 2;
        JLSTZ_OFFSET_DATA[4][2].x = 0;
        JLSTZ_OFFSET_DATA[4][2].y = 0;
        JLSTZ_OFFSET_DATA[4][3].x = -1;
        JLSTZ_OFFSET_DATA[4][3].y = 2;

        // I 블록 오프셋 데이터
        for (int i = 0; i < 5; ++i) {
            I_OFFSET_DATA.push_back(std::vector<Vector2Int>(4)); // 각 행(벡터) 생성
        }
        I_OFFSET_DATA[0][0].x = 0;
        I_OFFSET_DATA[0][0].y = 0;
        I_OFFSET_DATA[0][1].x = -1;
        I_OFFSET_DATA[0][1].y = 0;
        I_OFFSET_DATA[0][2].x = -1;
        I_OFFSET_DATA[0][2].y = 1;
        I_OFFSET_DATA[0][3].x = 0;
        I_OFFSET_DATA[0][3].y = 1;

        I_OFFSET_DATA[1][0].x = -1;
        I_OFFSET_DATA[1][0].y = 0;
        I_OFFSET_DATA[1][1].x = 0;
        I_OFFSET_DATA[1][1].y = 0;
        I_OFFSET_DATA[1][2].x = 1;
        I_OFFSET_DATA[1][2].y = 1;
        I_OFFSET_DATA[1][3].x = 0;
        I_OFFSET_DATA[1][3].y = 1;

        I_OFFSET_DATA[2][0].x = 2;
        I_OFFSET_DATA[2][0].y = 0;
        I_OFFSET_DATA[2][1].x = 0;
        I_OFFSET_DATA[2][1].y = 0;
        I_OFFSET_DATA[2][2].x = -2;
        I_OFFSET_DATA[2][2].y = 1;
        I_OFFSET_DATA[2][3].x = 0;
        I_OFFSET_DATA[2][3].y = 1;

        I_OFFSET_DATA[3][0].x = -1;
        I_OFFSET_DATA[3][0].y = 0;
        I_OFFSET_DATA[3][1].x = 0;
        I_OFFSET_DATA[3][1].y = 1;
        I_OFFSET_DATA[3][2].x = 1;
        I_OFFSET_DATA[3][2].y = 0;
        I_OFFSET_DATA[3][3].x = 0;
        I_OFFSET_DATA[3][3].y = -1;

        I_OFFSET_DATA[4][0].x = 2;
        I_OFFSET_DATA[4][0].y = 0;
        I_OFFSET_DATA[4][1].x = 0;
        I_OFFSET_DATA[4][1].y = -2;
        I_OFFSET_DATA[4][2].x = -2;
        I_OFFSET_DATA[4][2].y = 0;
        I_OFFSET_DATA[4][3].x = 0;
        I_OFFSET_DATA[4][3].y = 2;

        // O 블록 오프셋 데이터
        O_OFFSET_DATA.push_back(std::vector<Vector2Int>(4));
        O_OFFSET_DATA[0][0].x = 0;
        O_OFFSET_DATA[0][0].y = 0;
        O_OFFSET_DATA[0][1].x = 0;
        O_OFFSET_DATA[0][1].y = -1;
        O_OFFSET_DATA[0][2].x = -1;
        O_OFFSET_DATA[0][2].y = -1;
        O_OFFSET_DATA[0][3].x = -1;
        O_OFFSET_DATA[0][3].y = 0;
    }
};