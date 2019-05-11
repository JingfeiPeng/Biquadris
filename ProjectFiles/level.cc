#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include "level.h"

using namespace std;

Level::Level(int curLev, string filename):
curLev{curLev},filename{filename}{
    if(filename != ""){
        readFile();
    }
}

void Level::readFile(){
    if(filename == "")  {cerr << "error"; return;}
    char blk;
    ifstream f(filename);
    while(f >> blk){
        types.emplace_back(blk);
    }
}


void Level::countSetter(int c){};

int Level::countGetter(){
    //cout << "not level  four" << endl;
    return -1;
}
                

