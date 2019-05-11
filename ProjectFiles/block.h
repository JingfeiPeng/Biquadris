#ifndef _BLOCK_H_
#define _BLOCK_H_
#include <iostream>
#include "board.h"
#include "cell.h"
#include <math.h>
#include <vector>

struct Point {
  int x;
  int y;
};

//abstract Block class
class Block {
protected:
    char type;
    Point lowLeft;
    std::vector<Point> pLst;
    Board & board;
    int levelGen;
    int blockId;
    const int CLOCKWISE = 0;
    const int CCLOCKWISE = 1;
    const int rows = 18; // 15 rows + 3 reserved rows
    const int cols = 11;
    bool checkRotate(Point &newLowLeft,std::vector <Point> &newCoord, int direction);
    void updateLowerleft(Point &newLowLeft,std::vector <Point> &newCoord);
    bool checkBounds(std::vector<Point>,int, int);

public:
    Block(char, Point,std::vector <Point>, Board &, int, int);
    void rotate(int);
    bool shift(int x,int y);
    int drop();
    std::vector<Point> &getPLst();
    char getType();
    int getLevelGen();
    bool doConst(std::vector<Point> &);
    void resetCell();
};



class Iblock : public Block {
public:
    Iblock(Board &,int,int);
};

class Jblock : public Block{
public:
    Jblock(Board &,int, int);
};

class Lblock : public Block{
public:
    Lblock(Board &,int, int);
};

class Oblock : public Block{
public:
    Oblock(Board &,int, int);
};

class Sblock : public Block{
public:
    Sblock(Board &,int, int);
};

class Zblock : public Block{
public:
    Zblock(Board &,int, int);
};

class Tblock : public Block{
public:
    Tblock(Board &,int, int);
};

#endif
