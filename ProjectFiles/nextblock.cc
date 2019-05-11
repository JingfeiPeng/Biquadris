#include "nextblock.h"
#include <vector>
#include "view.h"
#include "cell.h"
using namespace std;


NextBlock::NextBlock(View* v,int xshif, int yshif){
    for (int i = 0; i < 2; i++){
        vector<Cell> temp;
        for (int j = 0; j < 4; j++){
            temp.emplace_back(Cell());
        }
        block.emplace_back(temp);
    }
    int x = 0;
    int y = 0;
    for(int i = 0; i < 2; i++){
        y += 2;
        for(int j = 0; j < 4; j++){
            x += 2;
            block[i][j].setCoords(x, y);
            block[i][j].setView(v);
            block[i][j].setPosn(xshif, yshif);
            block[i][j].set(0,' ',0);
            x -= 2;
            x += 30;
        }
        x = 0;
        y -= 2;
        y += 30;
    }
}

NextBlock::~NextBlock(){
    for (int i = 0; i < 2; i++){
        block[i].clear();
    }
    block.clear();
}

void NextBlock::setType(char t){
    type = t;
    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 4; j++){
            block[i][j].set(0,' ',0);
        }
    }
    if (type == 'I'){
        for(int i = 0; i < 4; i ++){
            block[1][i].set(0,'I',0);
        }
    }else if (type == 'J'){
        block[0][0].set(0,'J',0);
        block[1][0].set(0,'J',0);
        block[1][1].set(0,'J',0);
        block[1][2].set(0,'J',0);
    }else if (type == 'L'){
        block[0][2].set(0,'L',0);
        block[1][0].set(0,'L',0);
        block[1][1].set(0,'L',0);
        block[1][2].set(0,'L',0);
    }else if (type == 'O'){
        block[0][0].set(0,'O',0);
        block[1][0].set(0,'O',0);
        block[1][1].set(0,'O',0);
        block[0][1].set(0,'O',0);
    }else if (type == 'S'){
        block[0][1].set(0,'S',0);
        block[0][2].set(0,'S',0);
        block[1][0].set(0,'S',0);
        block[1][1].set(0,'S',0);
    }else if (type == 'Z'){
        block[0][0].set(0,'Z',0);
        block[0][1].set(0,'Z',0);
        block[1][2].set(0,'Z',0);
        block[1][1].set(0,'Z',0);
    }else if (type == 'T'){
        block[0][0].set(0,'T',0);
        block[0][1].set(0,'T',0);
        block[0][2].set(0,'T',0);
        block[1][1].set(0,'T',0);
    }
}


std::vector<std::vector<Cell>>& NextBlock::getgrid(){
    return block;
}

char NextBlock::getType(){
    return type;
}

