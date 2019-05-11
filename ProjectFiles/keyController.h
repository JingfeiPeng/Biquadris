#ifndef _KEYCONTROLLER_H_
#define _KEYCONTROLLER_H_
#include <fstream>
#include "boardManager.h"
#include "view.h"
#include "window.h"

class KeyController{
//    XEvent Event;
//    XWindow xw;
    bool graphic;
    int level;
    View view;
    Score scoreP1;
    Score scoreP2;
    BoardManager p1;
    BoardManager p2;
    void restartGame();
    void endGame();
    void resetGame();
    void askSpecialAction(BoardManager* target);
    public:
        KeyController(bool graphic, int level, std::string filename1 ,std::string filename2);
        void runGame();
};

#endif
