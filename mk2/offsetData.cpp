#include "offsetData.h"

offsetData* offsetData::sInstance = NULL;

offsetData* offsetData::Instance(){
    if(sInstance == NULL){
        sInstance = new offsetData();
    }
    return sInstance;
}
void offsetData::Release(){
    delete sInstance;
    sInstance = NULL;
}

offsetData::offsetData() : JLSTZ_OFFSET_DATA(), I_OFFSET_DATA(), O_OFFSET_DATA(){
    JLSTZ_offset_init();
    I_offset_init();
    O_offset_init();
}

offsetData::~offsetData(){ }

//getter
const std::vector<std::vector<vector2> >& offsetData::getJLSTZ_OFFSET_DATA() const{
    return JLSTZ_OFFSET_DATA;
}
const std::vector<std::vector<vector2> >& offsetData::getI_OFFSET_DATA() const{
    return I_OFFSET_DATA;
}
const std::vector<std::vector<vector2> >& offsetData::getO_OFFSET_DATA() const{
    return O_OFFSET_DATA;
}

//여기 밑으로는 offsetData vector 선언 하는 부분.
void offsetData::JLSTZ_offset_init(){
    /*
    {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{0, 0}, {1, 0}, {0, 0}, {-1, 0}},
    {{0, 0}, {1, -1}, {0, 0}, {-1, -1}},
    {{0, 0}, {0, 2}, {0, 0}, {0, 2}},
    {{0, 0}, {1, 2}, {0, 0}, {-1, 2}}
    */
    vector2 v0;
    std::vector<vector2> v1;
    std::vector<std::vector<vector2> > v2;

    v0.x = 0; v0.y = 0;
    v1.push_back(v0);
    v0.x = 0; v0.y = 0;
    v1.push_back(v0);
    v0.x = 0; v0.y = 0;
    v1.push_back(v0);
    v0.x = 0; v0.y = 0;
    v1.push_back(v0);
    v2.push_back(v1);
    v1.clear();
    
    v0.x = 0; v0.y = 0;
    v1.push_back(v0);
    v0.x = 1; v0.y = 0;
    v1.push_back(v0);
    v0.x = 0; v0.y = 0;
    v1.push_back(v0);
    v0.x = -1; v0.y = 0;
    v1.push_back(v0);
    v2.push_back(v1);
    v1.clear();

    v0.x = 0; v0.y = 0;
    v1.push_back(v0);
    v0.x = 1; v0.y = -1;
    v1.push_back(v0);
    v0.x = 0; v0.y = 0;
    v1.push_back(v0);
    v0.x = -1; v0.y = -1;
    v1.push_back(v0);
    v2.push_back(v1);
    v1.clear();

    v0.x = 0; v0.y = 0;
    v1.push_back(v0);
    v0.x = 0; v0.y = 2;
    v1.push_back(v0);
    v0.x = 0; v0.y = 0;
    v1.push_back(v0);
    v0.x = 0; v0.y = 2;
    v1.push_back(v0);
    v2.push_back(v1);
    v1.clear();

    v0.x = 0; v0.y = 0;
    v1.push_back(v0);
    v0.x = 1; v0.y = 2;
    v1.push_back(v0);
    v0.x = 0; v0.y = 0;
    v1.push_back(v0);
    v0.x = -1; v0.y = 2;
    v1.push_back(v0);
    v2.push_back(v1);
    v1.clear();

    const_cast<std::vector<std::vector<vector2> >&>(JLSTZ_OFFSET_DATA) = v2;
}

void offsetData::I_offset_init(){
    /*
    {{0, 0}, {-1, 0}, {-1, 1}, {0, 1}},
    {{-1, 0}, {0, 0}, {1, 1}, {0, 1}},
    {{2, 0}, {0, 0}, {-2, 1}, {0, 1}},
    {{-1, 0}, {0, 1}, {1, 0}, {0, -1}},
    {{2, 0}, {0, -2}, {-2, 0}, {0, 2}}
    */
    vector2 v0;
    std::vector<vector2> v1;
    std::vector<std::vector<vector2> > v2;

    v0.x = 0; v0.y = 0;
    v1.push_back(v0);
    v0.x = -1; v0.y = 0;
    v1.push_back(v0);
    v0.x = -1; v0.y = 1;
    v1.push_back(v0);
    v0.x = 0; v0.y = 1;
    v1.push_back(v0);
    v2.push_back(v1);
    v1.clear();
    
    v0.x = -1; v0.y = 0;
    v1.push_back(v0);
    v0.x = 0; v0.y = 0;
    v1.push_back(v0);
    v0.x = 1; v0.y = 1;
    v1.push_back(v0);
    v0.x = 0; v0.y = 1;
    v1.push_back(v0);
    v2.push_back(v1);
    v1.clear();

    v0.x = 2; v0.y = 0;
    v1.push_back(v0);
    v0.x = 0; v0.y = 0;
    v1.push_back(v0);
    v0.x = -2; v0.y = 1;
    v1.push_back(v0);
    v0.x = 0; v0.y = 1;
    v1.push_back(v0);
    v2.push_back(v1);
    v1.clear();

    v0.x = -1; v0.y = 0;
    v1.push_back(v0);
    v0.x = 0; v0.y = 1;
    v1.push_back(v0);
    v0.x = 1; v0.y = 0;
    v1.push_back(v0);
    v0.x = 0; v0.y = -1;
    v1.push_back(v0);
    v2.push_back(v1);
    v1.clear();

    v0.x = 2; v0.y = 0;
    v1.push_back(v0);
    v0.x = 0; v0.y = -2;
    v1.push_back(v0);
    v0.x = -2; v0.y = 0;
    v1.push_back(v0);
    v0.x = 0; v0.y = 2;
    v1.push_back(v0);
    v2.push_back(v1);
    v1.clear();

    const_cast<std::vector<std::vector<vector2> >&>(I_OFFSET_DATA) = v2;
}

void offsetData::O_offset_init(){
    /*
    {{0, 0}, {0, -1}, {-1, -1}, {-1, 0}}
    */
    vector2 v0;
    std::vector<vector2> v1;
    std::vector<std::vector<vector2> > v2;

    v0.x = 0; v0.y = 0;
    v1.push_back(v0);
    v0.x = 0; v0.y = -1;
    v1.push_back(v0);
    v0.x = -1; v0.y = -1;
    v1.push_back(v0);
    v0.x = -1; v0.y = 0;
    v1.push_back(v0);
    v2.push_back(v1);
    v1.clear();

    const_cast<std::vector<std::vector<vector2> >&>(O_OFFSET_DATA) = v2;
}