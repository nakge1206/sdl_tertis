#include "TetriMino.h"

//타입과 센터좌표를 입력으로 받는 생성자
TetriMino::TetriMino(MinoType _type, vector2 _position)
: type(_type), rotation(0), position(_position),
JLSTZ_OFFSET_DATA(offsetData::Instance()->getJLSTZ_OFFSET_DATA()),
I_OFFSET_DATA(offsetData::Instance()->getI_OFFSET_DATA()),
O_OFFSET_DATA(offsetData::Instance()->getO_OFFSET_DATA()){
    //블록 종류에 따라 타일 초기화
    //처음 넣는게 센터(0,0), x(+:right / -:left) y(+:up / -:down)
    switch (type) {
        case TTYPE_I: // I
        {
            SDL_Color Icolor = {253, 255, 255, 255};
            tiles.push_back(Tile(0, 0, Icolor));
            tiles.push_back(Tile(-1, 0, Icolor));
            tiles.push_back(Tile(1, 0, Icolor));
            tiles.push_back(Tile(2, 0, Icolor));
            break;
        }
        case TTYPE_J: // J
        {
            SDL_Color Jcolor = {0, 0, 255, 255};
            tiles.push_back(Tile(0, 0, Jcolor));
            tiles.push_back(Tile(-1, 0, Jcolor));
            tiles.push_back(Tile(-1, 1, Jcolor));
            tiles.push_back(Tile(1, 0, Jcolor));
            break;
        }
        case TTYPE_L: // L
        {
            SDL_Color Lcolor = {255, 165, 0, 255};
            tiles.push_back(Tile(0, 0, Lcolor));
            tiles.push_back(Tile(-1, 0, Lcolor));
            tiles.push_back(Tile(1, 0, Lcolor));
            tiles.push_back(Tile(1, 1, Lcolor));
            break;
        }
        case TTYPE_O: // O
        {
            SDL_Color Ocolor = {255, 255, 0, 255};
            tiles.push_back(Tile(0, 0, Ocolor));
            tiles.push_back(Tile(1, 0, Ocolor));
            tiles.push_back(Tile(0, 1, Ocolor));
            tiles.push_back(Tile(1, 1, Ocolor));
            break;
        }
        case TTYPE_S: // S
        {
            SDL_Color Scolor = {0, 0, 255, 255};
            tiles.push_back(Tile(0, 0, Scolor));
            tiles.push_back(Tile(-1, 0, Scolor));
            tiles.push_back(Tile(0, 1, Scolor));
            tiles.push_back(Tile(1, 1, Scolor));
            break;
        }
        case TTYPE_T: // T
        {
            SDL_Color Tcolor = {128, 0, 128, 255};
            tiles.push_back(Tile(0, 0, Tcolor));
            tiles.push_back(Tile(-1, 0, Tcolor));
            tiles.push_back(Tile(0, 1, Tcolor));
            tiles.push_back(Tile(1, 0, Tcolor));
            break;
        }
        case TTYPE_Z: // Z
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

void TetriMino::Rotate(bool clockwise, bool shouldOffset) {
    if(type == TTYPE_O) return; //O mino면 그대로
    int oldRotationIndex = rotation;
    //회전 상태: 시계방향이면 +1, 반시계방향이면 -1
    rotation += clockwise ? 1 : -1;
    rotation = Mod(rotation, 4);
    
    //회전 중심 타일 (센터를 기준으로)
    Tile center = tiles[0];

    // 모든 타일을 회전
    for (Tile& tile : tiles) {
        tile.RotateTile(center, clockwise);
    }

    if(!shouldOffset) return;

    bool canOffset = Offset(oldRotationIndex, rotation);

    if(!canOffset){
        Rotate(!clockwise, false);
    }
}

void TetriMino::Move_LR(char m){
    // 1. 이동 가능 여부 확인
    if (WillMove_LR(m)) {
        // 2. 이동 가능할 경우 블록 실제 이동
        if(m=='L'){ //Left
            position.x--;
        }else if(m=='R'){ //Right
            position.x++;
        }
    }
}
bool TetriMino::WillMove_LR(char m){
    vector2 nextPosition = position;
    if(m=='L'){
        nextPosition.x--;
    }else if(m=='R'){
        nextPosition.x++;
    }

    std::vector<Tile> currentTiles = tiles; 
    for (Tile& tile : currentTiles) {
        tile.relativePos.x += nextPosition.x;
        tile.relativePos.y += nextPosition.y;
    }

    for (const Tile& tile : currentTiles) {
        if (tile.relativePos.x < 0 || tile.relativePos.x >= 10 || tile.relativePos.y < 0) {
            return false;
        }
    }

    return true;
}

bool TetriMino::Offset(int oldRotIndex, int newRotIndex) {
    vector2 offsetVal1, offsetVal2, endOffset;

    // 블록 종류에 따라 오프셋 데이터 선택
    const std::vector<std::vector<vector2> >& curOffsetData =
        (type == TTYPE_O) ? O_OFFSET_DATA :
        (type == TTYPE_I) ? I_OFFSET_DATA : JLSTZ_OFFSET_DATA;

    endOffset = vector2(0, 0);

    bool movePossible=false;

    //오프셋표를 보면, [offset][old] - [offset][cur]의 위치로 센터의 좌표를 옮기는거임.
    for (int testOffset = 0; testOffset < 5; testOffset++) {
        offsetVal1 = curOffsetData[testOffset][oldRotIndex];
        offsetVal2 = curOffsetData[testOffset][newRotIndex];
        endOffset.x = offsetVal1.x - offsetVal2.x;
        endOffset.y = offsetVal1.y - offsetVal2.y;

        //센터를 endOffset으로 옮겼을때, 옮겨질 수 있는 곳인지확인 후 가능하면 종료
        if (CanMovePiece(endOffset)) {
            movePossible = true;
            break;
        }
    }

    return movePossible;
}

bool TetriMino::CanMovePiece(vector2 offset) {
    vector2 tmpPos;
    tmpPos.x = position.x + offset.x;
    tmpPos.y = position.y + offset.y;

    //바뀐 센터로부터의 Mino들이 조건에 다 부합하는지 확인해야함.
    std::vector<Tile> nextTiles = tiles;
    for (const Tile& tile : nextTiles) {
        //현재는 벽에 부딪히는거만 확인함.
        //todo: Grid 구현 후, 고정된 미노들과 충돌감지 부분 추가해야함.
        if (tmpPos.x + tile.relativePos.x < 0 ||tmpPos.x + tile.relativePos.x >= 10 ||tmpPos.y+ tile.relativePos.y < 0) {
            return false;
        }
    }

    position.x = tmpPos.x;
    position.y = tmpPos.y;
    return true;
}

int TetriMino::Mod(int x, int m){
    return (x % m + m) % m;
}

void TetriMino::Render(SDL_Renderer* renderer, int tileSize) {
    for (Tile& tile : tiles) {
        int startX = 44;
        int startY = 470;
        Tile tileToDraw = tile;
        tileToDraw.relativePos.x = startX + (position.x * tileSize) + (tile.relativePos.x * tileSize);
        tileToDraw.relativePos.y = startY - (position.y * tileSize) - (tile.relativePos.y * tileSize);

        tileToDraw.Render(renderer, tileSize);
    }
}


//디버그용
void TetriMino::ChangeType(MinoType newType){
    type = newType; // 블록 종류 변경
    tiles.clear(); // 기존 타일 정보 초기화

    // 새로운 블록 종류에 따라 타일 정보 다시 생성
    switch (type) {
        case TTYPE_I: // I
        {
            SDL_Color Icolor = {253, 255, 255, 255};
            tiles.push_back(Tile(0, 0, Icolor));
            tiles.push_back(Tile(-1, 0, Icolor));
            tiles.push_back(Tile(1, 0, Icolor));
            tiles.push_back(Tile(2, 0, Icolor));
            rotation = 0;
            break;
        }
        case TTYPE_J: // J
        {
            SDL_Color Jcolor = {0, 0, 255, 255};
            tiles.push_back(Tile(0, 0, Jcolor));
            tiles.push_back(Tile(-1, 0, Jcolor));
            tiles.push_back(Tile(-1, 1, Jcolor));
            tiles.push_back(Tile(1, 0, Jcolor));
            rotation = 0;
            break;
        }
        case TTYPE_L: // L
        {
            SDL_Color Lcolor = {255, 165, 0, 255};
            tiles.push_back(Tile(0, 0, Lcolor));
            tiles.push_back(Tile(-1, 0, Lcolor));
            tiles.push_back(Tile(1, 0, Lcolor));
            tiles.push_back(Tile(1, 1, Lcolor));
            rotation = 0;
            break;
        }
        case TTYPE_O: // O
        {
            SDL_Color Ocolor = {255, 255, 0, 255};
            tiles.push_back(Tile(0, 0, Ocolor));
            tiles.push_back(Tile(1, 0, Ocolor));
            tiles.push_back(Tile(0, 1, Ocolor));
            tiles.push_back(Tile(1, 1, Ocolor));
            rotation = 0;
            break;
        }
        case TTYPE_S: // S
        {
            SDL_Color Scolor = {0, 0, 255, 255};
            tiles.push_back(Tile(0, 0, Scolor));
            tiles.push_back(Tile(-1, 0, Scolor));
            tiles.push_back(Tile(0, 1, Scolor));
            tiles.push_back(Tile(1, 1, Scolor));
            rotation = 0;
            break;
        }
        case TTYPE_T: // T
        {
            SDL_Color Tcolor = {128, 0, 128, 255};
            tiles.push_back(Tile(0, 0, Tcolor));
            tiles.push_back(Tile(-1, 0, Tcolor));
            tiles.push_back(Tile(0, 1, Tcolor));
            tiles.push_back(Tile(1, 0, Tcolor));
            rotation = 0;
            break;
        }
        case TTYPE_Z: // Z
        {
            SDL_Color Zcolor = {255, 0, 0, 255};
            tiles.push_back(Tile(0, 0, Zcolor));
            tiles.push_back(Tile(1, 0, Zcolor));
            tiles.push_back(Tile(0, 1, Zcolor));
            tiles.push_back(Tile(-1, 1, Zcolor));
            rotation = 0;
            break;
        }
    }
}

void TetriMino::Move_UD(char m){
    if(m=='U'){ //Up
        position.y++;
    }else if(m=='D'){ //Down
        position.y--;
    }
}
