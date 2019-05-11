#ifndef _BOARD_MANEGER_H_
#define _BOARD_MANEGER_H_
#include <map>
#include <fstream>
#include "score.h"
#include "view.h"
#include "level.h"
#include "board.h"
#include "block.h"
#include "nextblock.h"
#include <memory>
#include "levelZero.h"
#include "levelOne.h"
#include "levelTwo.h"
#include "levelThree.h"
#include "levelFour.h"






class BoardManager {
    std::unique_ptr<Level> lev; // pointer to level object
    Score *score; // score Class.
    Board board;
    int blockId; // start at 0, ++ each time a new block generated.
    std::map<int,int> blockLst;
    std::unique_ptr<Block> curBlock;
    NextBlock nextBlock;
    //BoardManager * opponent;
    bool specialHeavy;
    std::string filename ;    // the source file for level 0
    void decideBlockType(std::unique_ptr<Block>& rBlock,char type);
    bool endGame = false;
    bool isBlind = false;
    
    //int horiShift = 0;
    //int vertiShift = 0;
    
    const int row = 18;
    const int rowReserved = 3;
    
    bool specialAction = false;
public:
    BoardManager(int level,std::string filename, Score *s,View*,int,int);
    void generateBlock();
    void decideLevelType(int level);
    bool moveBlock(int,int,int rep);
    bool rotateBlock(int direction, int rep); // clockwise 0, counterclockwise 1;
    void dropBlock(); // generate new block and new next block
    void checkDelete(int row, int height);
    void mutateBlock(char);
    void skipBlock();
    void levelUpDown(int, int);
    void switchRandom(std::string filename);
    int  getCurLev();
    Score* getScorePtr();

    Board& getBoard();
    //void setOpponent(BoardManager *);
    bool getEndGame();
    bool getIsBlind();
    int getCurScore();
    void setScore(Score *s);
    
    
    void showBlind();
    void unshowBlind();
    NextBlock& getNextBlock();
    //void setNextBlockType(char t);
    void setCurLev(int Curlev);
    Score& getScore();
    
    void unsetSpecialAction();
    void setSpecialHeavy();
    bool getSpecialAction();
    void unsetEndGame();

    
    void unsetSpecialHeavy();
    void addLevelCount();

    

    
    
};

#endif
