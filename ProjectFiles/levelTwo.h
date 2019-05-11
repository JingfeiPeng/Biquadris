
#ifndef LEVELTWO_H
#define LEVELTWO_H

#include <iostream>
#include <fstream>
#include <vector>
#include"level.h"

class LevelTwo : public Level{
public:
    LevelTwo();
    char createBlock() override;
};


#endif /* LEVELTWO_H */
