#ifndef _NEXTBLOCK_H
#define _NEXTBLOCK_H

#include <vector>
#include <iostream>
#include "cell.h"


class View;

class NextBlock{
    std::vector<std::vector<Cell>> block;
    char type = ' ';
public:
    NextBlock(View*,int,int);
    ~NextBlock();
    void setType(char);
    std::vector<std::vector<Cell>>& getgrid();
    char getType();
    
};



#endif
