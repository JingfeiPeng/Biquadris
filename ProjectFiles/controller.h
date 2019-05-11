#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_
#include <fstream>
#include "boardManager.h"
#include "view.h"


class Controller{
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
    Controller(bool graphic, int level, std::string filename1 ,std::string filename2);
    void runGame();
};


#endif
