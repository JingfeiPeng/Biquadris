#ifndef _VIEW_H_
#define _VIEW_H_
#include <iostream>
#include "window.h"
#include "board.h"
#include "level.h"
#include <memory>
//#include "score.h"

using namespace std;

class BoardManager;

class View{
    //bool isBlind;
   // BoardManager * p1;
    //BoardManager * p2;
    bool Graphical;
    std::unique_ptr<Xwindow> xw = nullptr;
public:
    View(bool graphical = true);
    int getPollEvent();
    void showText(BoardManager * p1, BoardManager * p2);
    void fillcell(int x, int y, int width, int colour);
    void fillstring(int x, int y, std::string ,int colour = Xwindow::White);
    void unfillstring(int x,int y, int width, int colour = Xwindow::Black);
    bool getGraphical();
    void endGame(BoardManager * p1, BoardManager * p2);
    
    
};



#endif

