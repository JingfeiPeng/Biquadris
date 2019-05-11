#include "levelTwo.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

LevelTwo::LevelTwo():
Level(2){}

char LevelTwo::createBlock(){
    int blk = rand() % 7;
    char newblk = 0;
    if (blk == 0){
        newblk = 'T';
    }else if (blk == 1){
        newblk = 'I';
    }else if (blk == 2){
        newblk = 'J';
    }else if (blk == 3){
        newblk = 'L';
    }else if (blk == 4){
        newblk = 'O';
    }else if (blk == 5){
        newblk = 'S';
    }else if (blk == 6){
        newblk = 'Z';
    }
    return newblk;
}
