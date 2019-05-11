#ifndef _CELL_H_
#define _CELL_H_
#include <iostream>
#include "window.h"

class View;

struct Cell {
    int blockId;
    char type;
    int levelGen;
    friend std::ostream &operator<<(std::ostream &out, const Cell &);
    
    int relativeX;
    int relativeY;
    int horiShift = 0;
    int vertiShift = 0;
    const int width = 26;
    View * view = nullptr;
    bool isBlind = false;
    int colour = Xwindow::White;
    
    
public:
    Cell();
    Cell& operator=(Cell &);
    
    
    void set(int,char,int);
    void reset(); // reset back to default value;
    char getType() const;
    
    
    void setCoords(int x, int y);
    void draw();
    void setPosn(int hori, int verti);
    void setView(View *);
    int getLevelGen();
    int getBlockId();
    
    void setIsBlind(bool b);
};

std::ostream &operator <<(std::ostream & out, const Cell &);

#endif


