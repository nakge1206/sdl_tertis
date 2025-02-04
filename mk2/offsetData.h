#pragma once

#include <iostream> //vector
#include "vector2.h" //vector2

//SRS회전 시스템의 OffsetData 2차원행렬 싱글톤 패턴
class offsetData {
public:
    //싱글톤 패턴 구현
    static offsetData* Instance();
    void Release();

    //getter
    const std::vector<std::vector<vector2> >& getJLSTZ_OFFSET_DATA() const;
    const std::vector<std::vector<vector2> >& getI_OFFSET_DATA() const;
    const std::vector<std::vector<vector2> >& getO_OFFSET_DATA() const;

private:
    static offsetData* sInstance;

    const std::vector<std::vector<vector2> > JLSTZ_OFFSET_DATA;
    const std::vector<std::vector<vector2> > I_OFFSET_DATA;
    const std::vector<std::vector<vector2> > O_OFFSET_DATA;

    void JLSTZ_offset_init();
    void I_offset_init();
    void O_offset_init();

    offsetData();
    ~offsetData();
};