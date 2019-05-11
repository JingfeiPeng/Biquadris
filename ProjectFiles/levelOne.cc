

#include "levelOne.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;


LevelOne::LevelOne():
Level(1){}

char LevelOne::createBlock(){
    int blk = rand() % 6;
    char newblk = 0;
    if (blk == 0){
        if(rand() % 2 == 0){
            newblk = 'S';
        }else{
            newblk = 'Z';
        }
    }else if (blk == 1){
        newblk = 'I';
    }else if (blk == 2){
        newblk = 'J';
    }else if (blk == 3){
        newblk = 'L';
    }else if (blk == 4){
        newblk = 'O';
    }else if (blk == 5){
        newblk = 'T';
    }
    return newblk;
}
