#include "board.h"
#include "cell.h"
#include <iostream>
#include "view.h"
#include "sstream"
#include <iomanip>
using namespace std;

Board::Board(View* v,int x, int y){
    view = v;
    horiShift = x;
    VertiShift = y;
    for (int i = 0; i < rows; i++){
        vector<Cell> tmpVec;
        for (int b = 0; b < cols; b++){
            tmpVec.emplace_back(Cell());
        }
        grid.emplace_back(tmpVec);
    }
    resetCoord();
    drawBoard();
}


void Board::clearBoard(){
    for (int i = 0; i < rows; i++){
        for (int b = 0; b < cols; b++){
            grid[i][b].reset();
        }
    }
}

Board::~Board(){
    for (int i = 0; i < rows; i++){
        grid[i].clear();
    }
    grid.clear();
}


std::vector <std::vector<Cell>> & Board::getGrid(){
    return grid;
}


void Board::resetCoord(){
    int x = 0;
    int y = 0;
    for(int i = 0; i < rows; i++){
        y += 2;
        for(int j = 0; j < cols; j++){
            x += 2;
            grid[i][j].setCoords(x, y);
            grid[i][j].setPosn(horiShift, VertiShift);
            grid[i][j].setView(view);
            x -= 2;
            x += 30;
        }
        x = 0;
        y -= 2;
        y += 30;
    }
}


void Board::drawBoard(){
    if(view == nullptr || !view->getGraphical())return;
    for(int i = 0; i < rows ; i++){
        for(int j = 0; j < cols; j++){
            grid[i][j].draw();
        }
    }
}



void Board::drawBlindBoard(){
        for(int i = 0; i < rows ; i++){
            for(int j = 0; j < cols; j++){
                if(i>= 5 && i <= 14 && j >= 2 && j <= 8){
                    grid[i][j].setIsBlind(true);
                    if(view->getGraphical())grid[i][j].draw();
                }
            }
        }
}


void Board::undrawBlindBoard(){
        for(int i = 0; i < rows ; i++){
            for(int j = 0; j < cols; j++){
                if(i >= 5 && i <= 14 && j >= 2 && j <= 8){
                    grid[i][j].setIsBlind(false);
                    if(view->getGraphical())grid[i][j].draw();
                }
            }
        }
}

void Board::setCurLev(int lev){
    CurLev = lev;
    drawLev();
}


void Board::drawLev(){
    if(view && view->getGraphical()){
        view->unfillstring(horiShift, VertiShift-20,80);
        ostringstream LevOss;
        LevOss<< "level:" << setfill(' ') << setw(5) << CurLev;
        string Lev = LevOss.str();
        view->fillstring(horiShift, VertiShift - 10, Lev);
    }
}
