#pragma once

#include "Tile.h"
#include "offsetData.h"
#include "Field.h"

class TetroMino {
public:
    //타입과 센터좌표를 입력으로 받는 생성자
    TetroMino(MinoType _type, vector2 _position);

    void Rotate(bool clockwise, bool shouldOffset = true);
    void Move(char m);
    bool WillMove(char m);

    void lock();

    void Render(SDL_Renderer* renderer);

    //디버그용 : 다양한 타입의 미노로 실험
    void ChangeType(MinoType newType);
    void Move_UD(char m);
private:
    Field* FieldData;

    std::vector<Tile> tiles;
    MinoType type;
    int rotation; //현재 회전 상태 (0, 1, 2, 3)
    vector2 position; //각 테트리미노의 센터 좌표(Field 좌표)

    //OffsetData는 참조로 받아옴.
    const std::vector< std::vector<vector2> >& JLSTZ_OFFSET_DATA;
    const std::vector< std::vector<vector2> >& I_OFFSET_DATA;
    const std::vector< std::vector<vector2> >& O_OFFSET_DATA;

    bool Offset(int oldRotIndex, int newRotIndex); //오프셋표 확인

    //센터의 Grid좌표에서, offset의 상태좌표를 다 더해줘야함.
    bool CanMovePiece(vector2 offset);

    int Mod(int x, int m);
};