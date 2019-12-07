#include <iostream>
#include "boardManager.h"
#include "cell.h"
#include "block.h"
#include "level.h"
using namespace std;

const int numOfCells = 4;

//new block, level, Board, level generated.


int BoardManager::getCurLev(){
    return lev->curLev;
}

Board& BoardManager::getBoard(){
    return board;
}

bool BoardManager::getIsBlind(){
    return isBlind;
}

int BoardManager::getCurScore(){
    return score->getCurScore();
}

void BoardManager::decideBlockType(std::unique_ptr<Block>& rBlock,char type){
    
    if (type == 'I'){
        rBlock = make_unique<Iblock>(board,lev->curLev, blockId);
    } else if (type == 'J'){
        rBlock = make_unique<Jblock>(board,lev->curLev, blockId);
    } else if (type == 'L'){
        rBlock = make_unique<Lblock>(board,lev->curLev, blockId);
    } else if (type == 'O'){
        rBlock = make_unique<Oblock>(board,lev->curLev, blockId);
    } else if (type == 'S'){
        rBlock = make_unique<Sblock>(board,lev->curLev, blockId);
    } else if (type == 'Z'){
        rBlock = make_unique<Zblock>(board,lev->curLev, blockId);
    } else if (type == 'T'){
        rBlock = make_unique<Tblock>(board,lev->curLev, blockId);
    }
    if(lev->curLev == 4 && lev->countGetter() == 6){
        for(int i = rowReserved; i < row; i++){
            if(board.getGrid()[i][5].getType() != ' ') {
                board.getGrid()[i - 1][5].set(-1, '*', 4); // setting the special block
                lev->countSetter(1);
                if(i - 1 == rowReserved || i == rowReserved) endGame = true;
                break;
            }
        }
        //what
        if(lev->countGetter()!= 1){
            board.getGrid()[row - 1][5].set(-1, '*', 4);
            lev->countSetter(1);
        }
    }
    if(!rBlock->doConst(rBlock->getPLst())){
        endGame = true;
    }
}


void BoardManager::unsetSpecialAction(){
    specialAction = false;
}

void BoardManager::addLevelCount(){
    lev->countSetter(lev->countGetter()+1);
}


void BoardManager::decideLevelType(int level){
    // check if new Level is valid;
    if (level == 0){
        lev = make_unique<LevelZero>(filename);
        setCurLev(0);
        score->setLevel(0);
    } else if (level == 1){
        lev = make_unique<LevelOne>();
        setCurLev(1);
        score->setLevel(1);
    } else if (level == 2){
        lev = make_unique<LevelTwo>();
        setCurLev(2);
        score->setLevel(2);
    } else if (level == 3){
        lev = make_unique<LevelThree>();
        setCurLev(3);
        score->setLevel(3);
    } else if (level == 4){
        lev = make_unique<LevelFour>();
        setCurLev(4);
        score->setLevel(4);
    }
}


void BoardManager::setScore(Score *s){
    score = s;
}


BoardManager::BoardManager(int level,string filename,Score *s,View * v, int x, int y):
lev{nullptr},score{s},board{Board(v,x,y)},blockId{0},curBlock{nullptr},nextBlock{NextBlock(v,x+210,y+560)},specialHeavy{false}, filename{filename}{
        score->resetCurScore();
        decideLevelType(level);
        decideBlockType(curBlock,lev->createBlock());
        blockLst[blockId] = 4;
        nextBlock.setType(lev->createBlock());
        
}


// move block according to x y
bool BoardManager::moveBlock(int x, int y,int repeat){
    bool switchplayer = false;
    while (repeat > 0){
        // if can't move
        curBlock->shift(x,y);
        --repeat;
    }
    // if can't move down further in level 3
    if (lev->curLev >= 3 && !curBlock->shift(0,1)){
        dropBlock();
        switchplayer = true;
    }
    // deal with if special action heavy is true
    if (y == 0 && specialHeavy && !curBlock->shift(0,2)){
        switchplayer = true;
        specialHeavy = false;
        dropBlock();
    }
    
    return switchplayer;
}

bool BoardManager::rotateBlock(int direction, int repeat){
    bool switchplayer = false;
    while (repeat > 0){
        curBlock->rotate(direction);
        --repeat;
    }
    // if can't move down further in level 3
    if (lev->curLev >= 3 && !curBlock->shift(0,1)){
        dropBlock();
        switchplayer = true;
    }
    return switchplayer;
}


// up = +1, down =  -1
void BoardManager::levelUpDown(int upDown, int repeat){
    while (repeat > 0){
        int curLevNum = lev->curLev;
        if (curLevNum + upDown >= 0 && curLevNum + upDown <= 4){
            curLevNum += upDown;
            decideLevelType(curLevNum);
            //board.setCurLev(curLevNum);
            //score->setLevel(curLevNum);
        }
        repeat--;
    }
}



void BoardManager::generateBlock(){
    ++blockId;
    blockLst[blockId] = 4;
    decideBlockType(curBlock,nextBlock.getType());
    nextBlock.setType(lev->createBlock());
}


void BoardManager::skipBlock(){
    ++blockId;
    blockLst[blockId] = 4;
    curBlock->resetCell();
    decideBlockType(curBlock,nextBlock.getType());
    lev->countSetter(lev->countGetter()-1);
    nextBlock.setType(lev->createBlock());
}

Score* BoardManager::getScorePtr(){
    return score;
}


void BoardManager::dropBlock(){ // generate new block and new next block
    int blockPos = curBlock->drop();
    const int numPoints = 4;
    if(isBlind)unshowBlind();
    checkDelete(blockPos, numPoints);
    generateBlock();
}


void BoardManager::mutateBlock(char typeB){
    curBlock->resetCell();
    decideBlockType(curBlock, typeB);
}

void BoardManager::setSpecialHeavy(){
    specialHeavy = true;
}


bool BoardManager::getSpecialAction(){
    return specialAction;
}



// deal with map and the blockids
void BoardManager::checkDelete(int row, int height){
    const int numCols = 11;
    int count = 0;
    int upperLimit = row - height;
    for (int i = row; i > upperLimit; i--) {
        bool rowFull = true;
        for (int b = 0; b < numCols; b++) {
            if (board.getGrid()[i][b].getType() == ' ') {
                rowFull = false;
            }
        }
        if (rowFull) {
            lev->countSetter(1);
            for (int b = 0; b < numCols; b++) {
                int id = board.getGrid()[i][b].getBlockId();
                if (blockLst[id] > 1) {
                    blockLst[id] = blockLst[id] - 1;
                } else {
                    score->blockEliminated(board.getGrid()[i][b].getLevelGen());
                    blockLst.erase(id);
                }
            }
            board.getGrid().erase(board.getGrid().begin()+i);
            vector<Cell> addBack;
            for (int a = 0; a < numCols; a++) {
                Cell toAdd{};
                addBack.emplace_back(toAdd);
            }
            auto it = board.getGrid().begin();
            it = board.getGrid().insert(it, addBack);
            count++;
            ++i;
            upperLimit++;
            board.resetCoord();
            board.drawBoard();
        }
    }
    if (count > 0) {
        score->rowEliminated(count);
    }
    if (count > 1) {
        specialAction = true;
    }
}

void BoardManager::unsetEndGame(){
    endGame = false;
}

bool BoardManager::getEndGame(){
    return endGame;
}

void BoardManager::switchRandom(string sor){
    if (sor != "" && lev->curLev == 3){
        lev = make_unique<LevelThree>(sor);
        //lev->setFromFile(true);
    } else if (sor != "" && lev->curLev == 4){
        lev = make_unique<LevelFour>(sor);
        //lev->setFromFile(true);
    } else if (sor == ""  && lev->curLev == 3){
        lev = make_unique<LevelThree>();
        //lev->setFromFile(false);
    } else if (sor == "" && lev->curLev == 4){
        lev = make_unique<LevelFour>();
        //lev->setFromFile(false);
    }
}


void BoardManager::showBlind(){
    isBlind = true;
    board.drawBlindBoard();
    
}
void BoardManager::unshowBlind(){
    isBlind = false;
    board.undrawBlindBoard();
}

NextBlock& BoardManager::getNextBlock(){
    return nextBlock;
}


void BoardManager::setCurLev(int l){
    board.setCurLev(l);
}


Score& BoardManager::getScore(){
    return *score;
}



void BoardManager::unsetSpecialHeavy(){
    specialHeavy = false;
}


