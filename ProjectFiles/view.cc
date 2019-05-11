#include "view.h"
#include "boardManager.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include "sstream"
#include <iomanip>
#include <vector>
#include "cell.h"
#include "window.h"
#include "score.h"
using namespace std;


View::View(bool graphical):
Graphical{graphical},xw{nullptr}{
    
    if(Graphical){
        xw = make_unique<Xwindow>(960,780);
        xw->fillRectangle(0, 0, 960, 780,Xwindow::Black);
        xw->drawBigString(330, 80, "Biquadris", Xwindow::White);
        xw->drawString(100, 680, "Next:",Xwindow::White);
        xw->drawString(540, 680, "Next:",Xwindow::White);
    }
}

int View::getPollEvent(){
    return xw->pollEvent();
}


const int numRows = 18;
const int numCols = 11;

bool View::getGraphical(){
    return Graphical;
}

void View::fillcell(int x, int y, int width, int colour){
    if(Graphical){
        xw->fillRectangle( x,  y, width,width, colour);
    }
}

void View::fillstring(int x, int y, std::string msg ,int colour){
    if(Graphical){
        xw->drawString(x,y,msg,colour);
    }
}

void View::unfillstring(int x,int y, int width, int colour){
    if(Graphical){
        xw->fillRectangle(x, y, width, 20,colour);
    }
}



void View::showText(BoardManager * p1, BoardManager * p2){
    cout << "level:" << setfill(' ') << setw(5) << p1->getCurLev();
    cout << "     " ;
    cout <<"level:" << setfill(' ') << setw(5) << p2->getCurLev()<< endl;
    cout << "Score:" << setfill(' ') << setw(5) << p1->getCurScore();
    cout << "     " ;
    cout <<"Score:" << setfill(' ') << setw(5) << p2->getCurScore()<< endl;
     
    cout <<"-----------     -----------" <<endl;
    for (int i  = 0; i < numRows; i++){
        for(int j = 0; j < numCols; j++){
                cout << p1->getBoard().getGrid()[i][j];
        }
        cout << "     " ;
        for(int j = 0; j < numCols; j++){
                cout << p2->getBoard().getGrid()[i][j];
        }
        cout << endl;
    }
    cout <<"-----------     -----------" <<endl;
    cout <<"Next:           Next:      " << endl;
    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 4; j++){
            cout << p1->getNextBlock().getgrid()[i][j];
        }
        cout << "      ";
        cout << "      ";
        for (int j = 0; j < 4; j++){
            cout << p2->getNextBlock().getgrid()[i][j];
        }
        cout << endl;
    }
}


void View::endGame(BoardManager * p1, BoardManager *  p2){
    if (!Graphical) return;
    int p1Score = p1->getScore().getHighScore();
    int p2Score = p2->getScore().getHighScore();
    string winner;
    if(p1Score > p2Score) {
        winner = "Player 1 Wins!";
    }
    else if(p1Score < p2Score){
        winner = "Player 2 Wins!";
    }
    else{
        winner = "This is a Tie!";
    }
    xw->fillRectangle(370,300,230,90,Xwindow::Black);
    xw->drawString(400,330,"Player 1 highest score:   " + to_string(p1Score),Xwindow::White);
    xw->drawString(400,350,"Player 2 highest score:   " + to_string(p2Score),Xwindow::White);
    xw->drawString(400,370, winner ,Xwindow::White);
}

