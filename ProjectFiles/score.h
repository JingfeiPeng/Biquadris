#ifndef _SCORE_H_
#define _SCORE_H_
#include <iostream>

class View;

class Score{
    int curScore;
    int highScore;
    int level;
    
    View * view = nullptr;
    int horiShift;
    int VertiShift;
    void drawScore();
    
    
public:
    explicit Score(int lev,View*,int,int);
    void rowEliminated(int);
    void blockEliminated(int);
    void setLevel(int);
    void resetCurScore();
    int getCurScore();
    int getHighScore();
    void addCurScore(int);

};



#endif
