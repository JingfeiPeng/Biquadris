
#include "levelFour.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

LevelFour::LevelFour(string filename):
Level(4,filename){}


void LevelFour::countSetter(int c){
    count = c;
}


int LevelFour::countGetter(){
    //cout << "level  four" << endl;
    return count;
}


char LevelFour::createBlock(){
    count++;
    if(filename != ""){
        int size = types.size();
        if (index == size){
            index = 0;
        }
        char newblk = types[index];
        index++;
        return newblk;
    }
    int blk = rand() % 9;
    char newblk = 0;
    if (blk == 0 || blk == 1){
        newblk = 'S';
    }else if (blk == 2 || blk == 3){
        newblk = 'Z';
    }else if (blk == 4){
        newblk = 'I';
    }else if (blk == 5){
        newblk = 'J';
    }else if (blk == 6){
        newblk = 'L';
    }else if (blk == 7){
        newblk = 'O';
    }else if (blk == 8){
        newblk = 'T';
    }
    return newblk;
}

