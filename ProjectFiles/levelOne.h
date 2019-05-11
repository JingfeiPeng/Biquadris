#ifndef LEVELONE_H
#define LEVELONE_H

#include"level.h"
#include <iostream>
#include <fstream>
#include <vector>


class LevelOne : public  Level{
public:
    LevelOne();
    char createBlock() override;
    //int countGetter() override;
};


#endif /* LEVELONE_H */
