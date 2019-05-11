#ifndef LEVELFOUR_H
#define LEVELFOUR_H

#include"level.h"
#include <iostream>
#include <fstream>
#include <vector>


class LevelFour : public Level{
    int count = 0;
public:
    LevelFour(std::string filename = "");
    char createBlock() override;
    void countSetter(int c) override;
    int countGetter() override;
};


#endif
