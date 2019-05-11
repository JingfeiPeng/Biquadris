#include "score.h"
#include "boardManager.h"
#include "view.h"
#include <sstream>
#include <iomanip>
using namespace std;


Score::Score(int lev,View* v,int x,int y):curScore{0},highScore{0},level{lev}, view{v},horiShift{x},VertiShift{y}{}


int Score::getHighScore(){
    return highScore;
}

void Score::addCurScore(int addAmount){
    curScore += addAmount;
    drawScore();
}

void Score::rowEliminated(int numOfRows){
    curScore += (numOfRows+level)*(numOfRows+level);
    drawScore();
    if (curScore > highScore) highScore = curScore;
}

int Score::getCurScore(){
    return curScore;
}

void Score::blockEliminated(int lev){
    curScore += (lev+1)*(lev+1);
    drawScore();
    if (curScore > highScore) highScore = curScore;
}

void Score::setLevel(int newLev){
    level = newLev;
}

void Score::resetCurScore(){
    curScore = 0;
    drawScore();
}


////
/*
void Score::setView(View *v){
    view = v;
}
void Score::setPosn(int hori, int verti){
    horiShift = hori;
    VertiShift = verti;
}
 */

void Score::drawScore(){
    view->unfillstring(horiShift+250, VertiShift-20, 80);
    ostringstream ScoOss;
    ScoOss<< "Score:" << setfill(' ') << setw(5) << curScore;
    string msg = ScoOss.str();
    view->fillstring(horiShift + 250, VertiShift - 10, msg);
}
