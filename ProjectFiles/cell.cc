#include <iostream>
#include "cell.h"
#include "window.h"
#include "view.h"
using namespace std;


Cell::Cell(){
    blockId = -1;
    type = ' ';
    levelGen  = -1;
    //colour = Xwindow::White;
}

Cell& Cell::operator=(Cell & cell){
    blockId = cell.blockId;
    type = cell.type;
    levelGen = cell.levelGen;
    colour = cell.colour;
    return *this;
}

void Cell::reset(){ // reset back to default value;
    blockId = -1;
    type = ' ';
    levelGen = -1;
    colour = Xwindow::White;
    draw();
} 

void Cell::set(int id,char typ,int levGen){
    blockId = id;
    type = typ;
    levelGen = levGen;
    if(type == 'I'){
        colour = Xwindow::Red;
    }else if(type == 'J'){
        colour = Xwindow::Blue;
    }else if(type == 'L'){
        colour = Xwindow::Cyan;
    }else if(type == 'O'){
        colour = Xwindow::Yellow;
    }else if(type == 'S'){
        colour = Xwindow::Magenta;
    }else if(type == 'Z'){
        colour = Xwindow::Orange;
    }else if(type == '*'){
        colour = Xwindow::Brown;
    }else if(type == 'T'){
        colour = Xwindow::DarkGreen;
    }else if(type == ' '){ ////for NextBlock Use Only
        colour = Xwindow::Black;
    }
    draw();
}


ostream &operator<<(ostream &out, const Cell &cell){
    if(cell.isBlind){
        out << '?';
    }else{
    out << cell.getType();
    }
    return out;
} 


char Cell::getType() const{
    return type;
}


void Cell::setCoords(int x, int y){
    relativeX = x;
    relativeY = y;
}

void Cell::draw(){
    if(view == nullptr) return;
    if(!view->getGraphical())return;
    if(isBlind){
        view->fillcell(relativeX+horiShift,relativeY+vertiShift,width,Xwindow::Black);
        return;
    }else{
        view->fillcell(relativeX+horiShift,relativeY+vertiShift,width,colour);
    }
}


void Cell::setPosn(int hori, int verti){
    horiShift = hori;
    vertiShift = verti;
}


int Cell::getLevelGen(){
    return levelGen;
}


int Cell::getBlockId(){
    return blockId;
}

void Cell::setView(View* v){
    view = v;
}


void Cell::setIsBlind(bool b){
    isBlind = b;
}
