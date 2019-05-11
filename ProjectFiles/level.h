#include <iostream>
#include <fstream>
#include <vector>

#ifndef _LEVEL_H_
#define _LEVEL_H_

class Level {
public:
    int curLev;
protected:
    int index = 0;
    std::string filename;
    std::vector<char> types;
public:
    Level(int curLev, std::string filename = "");
    virtual ~Level() = default;
    
    
    virtual char createBlock() = 0;
    void readFile();
    virtual void countSetter(int c);
    virtual int countGetter();
};



#endif
