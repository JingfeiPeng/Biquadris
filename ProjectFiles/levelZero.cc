#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "levelZero.h"
using namespace std;

LevelZero::LevelZero(string filename):
Level(0,filename){}


char LevelZero::createBlock(){
    int size = types.size();
    if (index == size){
        index = 0;
    }
    char newblk = types[index];
    index++;
    return newblk;
}
