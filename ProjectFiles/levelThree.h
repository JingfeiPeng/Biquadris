
#ifndef LEVELTHREE_H
#define LEVELTHREE_H

#include"level.h"
#include <iostream>
#include <fstream>
#include <vector>


class LevelThree : public Level{
public:
    LevelThree(std::string filename = "");
    char createBlock() override;
};


#endif /* LEVELTHREE_H */
