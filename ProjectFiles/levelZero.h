#ifndef LEVELZERO_H
#define LEVELZERO_H

#include <iostream>
#include <fstream>
#include <vector>

#include"level.h"

class LevelZero : public Level{
public:
    LevelZero(std::string filename);
    char createBlock() override;
    //int countGetter() override;
    
};

#endif 
