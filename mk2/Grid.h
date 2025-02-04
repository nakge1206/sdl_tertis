#pragma once

#include "TetroMino.h"

struct grid
{
    int x, y;
    int type;
};


class Field{
public:

private:
    std::vector< std::vector<grid> > Grid;

};