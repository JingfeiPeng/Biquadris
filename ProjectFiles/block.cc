#include "block.h"
#include <vector>
using namespace std;

const int numRowsReserved = 3;


Block::Block(char type, Point lowLeft, std::vector <Point> pLst, Board &board, int levelGen, int blockId):
  type{type}, lowLeft{lowLeft}, pLst{pLst},
  board{board},levelGen{levelGen}, blockId{blockId}{}


bool Block::shift(int x,int y){
    int length = pLst.size();
    if(checkBounds(pLst, x, y)) {
        for(int i = 0; i < length; i++) {
            board.getGrid()[pLst[i].y][pLst[i].x].reset();
            pLst[i].x += x;
            pLst[i].y += y;
        }
        for(int i = 0; i < length; i++) {
            board.getGrid()[pLst[i].y][pLst[i].x].set(blockId, type, levelGen);
        }
    } else {
        return false;
    }
    lowLeft.x += x;
    lowLeft.y += y;
    return true;
}

bool Block::checkBounds(std::vector<Point> pLst,int x, int y){
    int length = pLst.size();
    for(int i = 0; i < length; i++) {
        if (pLst[i].x + x < 0 || pLst[i].x + x > cols - 1 || pLst[i].y + y > rows - 1 || pLst[i].y + y < 0 ||
        (board.getGrid()[pLst[i].y + y][pLst[i].x + x].getType() != ' ' && board.getGrid()[pLst[i].y + y][pLst[i].x + x].getBlockId() != blockId)) {
            return false;
        }
    }
    return true;
}

void Block::resetCell() {
	const int numCells = 4;
	for (int i = 0; i < numCells; i++) {
		board.getGrid()[pLst[i].y][pLst[i].x].reset();
	}
}


int Block::drop(){
    int length = pLst.size();
    int count = 0;
    while (checkBounds( pLst, 0, 1)) {
        for(int i = 0; i < length; i++) {
            board.getGrid()[pLst[i].y][pLst[i].x].reset();
            pLst[i].y += 1;
        }
        count++;
    }
    for(int i = 0; i < length; i++){
        board.getGrid()[pLst[i].y][pLst[i].x].set(blockId, type, levelGen);
    }
    lowLeft.y += count;
    return lowLeft.y;
}

char Block::getType(){
    return type; 
}

int Block::getLevelGen(){
    return levelGen;
}

std::vector<Point> & Block::getPLst(){
    return pLst;
}


//private
void Block::updateLowerleft(Point &newLowLeft, std::vector <Point> &newCoord){
    int lowest_x = newCoord[0].x;
    int highest_y = newCoord[0].y;
    int length = newCoord.size();
    for(int i = 0; i < length; i++) {
        if(newCoord[i].x < lowest_x) {
            lowest_x = newCoord[i].x;
        }
        if(newCoord[i].y > highest_y) {
            highest_y = newCoord[i].y;
        }
    }
    newLowLeft.x = lowest_x;
    newLowLeft.y = highest_y;
}

bool Block::checkRotate(Point &newLowLeft,std::vector <Point> &newCoord, int direction) {
    int x_diff = 0;
    int y_diff = 0;
    int length = newCoord.size();
    int temp = 0;
    for(int i = 0; i < length; i++) {
        newCoord[i].x -= lowLeft.x;
        newCoord[i].y -= lowLeft.y;
        temp = newCoord[i].y;
        newCoord[i].y = (int)pow(-1, direction) * newCoord[i].x;
        newCoord[i].x = (int)pow(-1, direction + 1) * temp;
    }
    updateLowerleft(newLowLeft, newCoord);
    x_diff = lowLeft.x - newLowLeft.x;
    y_diff = lowLeft.y - newLowLeft.y;
    for (int i = 0; i < length; ++i) {
        newCoord[i].x += x_diff;
        newCoord[i].y += y_diff;
    }
    return checkBounds(newCoord, 0, 0);
}

void Block::rotate(int direction){
    int length = pLst.size();
    std::vector <Point> newCoord;
    Point newLowLeft{0,0};
    for(int i = 0; i < length; i++) {
        newCoord.emplace_back(pLst[i]);
    }
    if(checkRotate(newLowLeft, newCoord, direction)) {
        for (int i = 0; i < length; ++i) {
            board.getGrid()[pLst[i].y][pLst[i].x].reset();
        }
        for (int i = 0; i < length; ++i) {
            board.getGrid()[newCoord[i].y][newCoord[i].x].set(blockId, type, levelGen);
        }
        pLst = newCoord;
    }
}


bool Block::doConst(std::vector<Point> & pLst){
    int length = pLst.size();
    int count = 0;
    for(int i = 0; i < length; i++) {
        count++;
        if ( board.getGrid()[pLst[i].y][pLst[i].x].getType() == ' ') {
            board.getGrid()[pLst[i].y][pLst[i].x].set(blockId, type, levelGen);
        } else {
            return false;
        }
    }
    return true;
}




// I-Block

Iblock::Iblock(Board &board,int levelGen, int blockId):
        Block('I',Point{0, 3}, std::vector<Point>{Point{0, 3}, Point{1, 3}, Point{2, 3}, Point{3, 3}},
              board, levelGen, blockId){}


// J-Block

Jblock::Jblock(Board &board,int levelGen, int blockId):
        Block('J',Point{0, 3}, std::vector<Point>{Point{0, 2}, Point{0, 3}, Point{1, 3}, Point{2, 3}},
              board, levelGen, blockId){}

// L-Block


Lblock::Lblock(Board &board,int levelGen, int blockId):
        Block('L',Point{0, 3}, std::vector<Point>{Point{0, 3}, Point{1, 3}, Point{2, 3}, Point{2, 2}},
              board, levelGen, blockId){}

// O-Block


Oblock::Oblock(Board &board,int levelGen, int blockId):
        Block('O',Point{0, 3}, std::vector<Point>{Point{0, 2}, Point{0, 3}, Point{1, 2}, Point{1, 3}},
              board, levelGen, blockId){}


// S-Block


Sblock::Sblock(Board &board,int levelGen, int blockId):
        Block('S',Point{0, 3}, std::vector<Point>{Point{0, 3}, Point{1, 3}, Point{1, 2}, Point{2, 2}},
              board, levelGen, blockId){}


// Z-Block


Zblock::Zblock(Board &board,int levelGen, int blockId):
        Block('Z',Point{0, 3}, std::vector<Point>{Point{0, 2}, Point{1, 2}, Point{1, 3}, Point{2, 3}},
              board, levelGen, blockId){}


// T-Block


Tblock::Tblock(Board &board,int levelGen, int blockId):
        Block('T',Point{0, 3}, std::vector<Point>{Point{0, 2}, Point{1, 2}, Point{2, 2}, Point{1, 3}},
              board, levelGen, blockId){}

