#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <cstdlib>
#include "view.h"
#include "keyController.h"
#include "controller.h"
using namespace std;


int main(int args, char *argv[]){ // args  default 1, the name of program
    bool graphic = true;
    int count = 1;
    int level = 0;
    string in1 = "sequence1.txt" ;
    string in2 = "sequence2.txt" ;
    bool isBonus = false;
    while (count < args){
        string command = argv[count];
        if (command == "-text"){
            graphic  = false;
        }
        if (command == "-enablebonus"){
            isBonus = true;
        } 
        if (command  == "-seed"){
            unsigned int seeds;
            ++count;
            string num = argv[count];
            istringstream iss{num};
            iss >> seeds;
            srand(seeds);
        }
        if (command == "-scriptfile1"){
            ++count;
            string file = argv[count];
            in1 = file;
        }
        if (command == "-scriptfile2"){
            ++count;
            string file = argv[count];
            in2 = file;
        }
        if (command == "-startlevel"){
            ++count;
            string numLev = argv[count];
            istringstream iss{numLev};
            iss >> level;
        }
        ++count;
    }
    if(isBonus) {
        KeyController keyController{graphic, level, in1, in2};
        keyController.runGame();
    } else {
        Controller control{graphic,level,in1,in2};
        control.runGame();
    }
}
