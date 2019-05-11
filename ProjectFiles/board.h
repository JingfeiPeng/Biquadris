#ifndef _BOARD_H_
#define _BOARD_H_
#include <vector>
#include "cell.h"
#include <iostream>

class View;

class Board {
    std::vector <std::vector<Cell> > grid; // the 15rows 11 column board
    const int rows = 18; // 15 rows + 3 reserved rows
    const int cols = 11;     //不应该是declaration吗？
    View * view = nullptr;
   // bool isBlind = false;
    
    int horiShift;
    int VertiShift;
    
    int CurLev;
    
public:
    Board(View *,int,int);
    ~Board();
    void clearBoard();
    std::vector <std::vector<Cell>> & getGrid();
    

    void resetCoord(); //call everytime a row is pop, reset the coord of cell on the grid
    void drawBoard();
    //void setBlind();
    
    //void setPosn(int hori, int verti);
   // void setView(View *);
    
    void drawBlindBoard();
    void undrawBlindBoard();
    void setCurLev(int lev);
    void drawLev();
};



#endif

