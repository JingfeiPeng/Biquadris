#include <iostream>
#include "controller.h"
#include "view.h"
#include "boardManager.h"
#include <sstream>
#include <fstream>
#include "score.h"
using namespace std;

Controller::Controller(bool graphic, int level,string filename1,string filename2):
graphic{graphic},level{level},view{View(graphic)},scoreP1{Score(level,&view,100,120)},scoreP2{Score(level,&view,540,120)},p1{BoardManager(level,filename1,&scoreP1,&view,100,120)},p2{BoardManager(level,filename2, &scoreP2,&view,540,120)}{}


// broadManager should clear Board;
void Controller::restartGame(){
    cout << "Player 1's score: " << scoreP1.getCurScore() <<endl;
    cout << "Player 2's score: " << scoreP2.getCurScore() <<endl;
    if (scoreP1.getCurScore() > scoreP2.getCurScore()){
        cout << "Player 1 Won! Happy Chicken Dinner" << endl;
    } else if (scoreP1.getCurScore() < scoreP2.getCurScore()){
        cout << "Player 2 Won! Happy Chicken Dinner!" << endl;
    } else{
        cout << "This is a tie!" << endl;
    }
    resetGame();
}

void Controller::resetGame(){
    scoreP1.resetCurScore();
    scoreP2.resetCurScore();
    p1.getBoard().clearBoard();
    p2.getBoard().clearBoard();
    p1.decideLevelType(p1.getCurLev());
    p2.decideLevelType(p1.getCurLev());
    p1.generateBlock();
    p2.generateBlock();
    // add level counter by 1
    p1.addLevelCount();
    p2.addLevelCount();
    p1.unsetEndGame();
    p2.unsetEndGame();
    p1.unsetSpecialAction();
    p2.unsetSpecialAction();
    p1.unshowBlind();
    p2.unshowBlind();
    p1.unsetSpecialHeavy();
    p2.unsetSpecialHeavy();
}

void Controller::askSpecialAction(BoardManager* target){
    while (true) {
        cout << "Choose a special action by typing either:" << endl;
        cout << "blind\nheavy\nforce" << endl;
        string specialAction;
        cin >> specialAction;
        if (specialAction == "blind") {
            target->showBlind();
            view.showText(&p1,&p2);
            break;
        } else if (specialAction == "heavy") {
            target->setSpecialHeavy();
            view.showText(&p1,&p2);
            break;
        } else if (specialAction == "force") {
            cout << "Enter a block Type (Capital Letter)" << endl;
            char newType = 'm';
            cin >> newType;
            while (newType !='I' && newType != 'J' && newType !='L' && newType !='O' &&
                   newType !='S' && newType !='Z' && newType !='T') {
                cout << "Enter I, J, L, O, S, Z, or T" << endl;
                cin >> newType;
                if (cin.eof()) return;
            }
            target->mutateBlock(newType);
            view.showText(&p1,&p2);
            break;
        } else {
            cout << "Please enter a valid special action." << endl;
        }
    }
}

void Controller::endGame(){
    cout << "Player 1's score: " << scoreP1.getCurScore() <<endl;
    cout << "Player 2's score: " << scoreP2.getCurScore() <<endl;
    if (scoreP1.getCurScore() > scoreP2.getCurScore()){
        cout << "Player 1 Wins! Happy Chicken Dinner" << endl;
    } else if (scoreP1.getCurScore() < scoreP2.getCurScore()){
        cout << "Player 2 Wins! Happy Chicken Dinner!" << endl;
    } else{
        cout << "This is a tie!" << endl;
    }
    resetGame();
    string reset = "";
    while (reset != "r" && reset != "e"){
        cout << "Press r to Reset Game and e to endGame" << endl;
        cin >> reset;
        if (cin.eof()) return;
    }
    if (reset == "r"){
        cin.ignore();
        runGame();
    } else{
        // the game ended, compare the highest score
        cout << "Player 1's highest score: " << scoreP1.getHighScore() <<endl;
        cout << "Player 2's highest score: " << scoreP2.getHighScore() <<endl;
        if (scoreP1.getHighScore() > scoreP2.getHighScore()){
            cout << "Player 1 has the highest score\nThe winner is Player1!" << endl;
        } else if (scoreP1.getHighScore() < scoreP2.getHighScore()){
            cout << "Player 2 has the highest score\nThe winner is Player2!" << endl;
        } else{
            cout << "This is a tie!" << endl;
        }
        view.endGame(&p1,&p2);
        cout << "Enter anything to quit"<< endl;
        cin>> reset;
    }
}

void Controller::runGame(){
    string command;
    BoardManager *cur = &p1;
    ifstream fileInput;
    bool useFile =false;
    while (true){
        view.showText(&p1,&p2);
        //check if specialAction activated
        if (p1.getSpecialAction()){
            askSpecialAction(&p2);
            p1.unsetSpecialAction();
        } else if (p2.getSpecialAction()){
            askSpecialAction(&p1);
            p2.unsetSpecialAction();
        }

        if (useFile) {
            if (!(fileInput >> command)){
                useFile = false;
                if (!(cin >> command)){
                   break;
                }
            } else {
                cout << command << endl;
            }
        } else if (!(cin >> command)) {
            break;
        }
        istringstream iss{command};
        string partCommand;
        int repeat = 1;
        if (!(iss >> repeat)){
            iss.clear();
            repeat = 1;
        }
        iss >> partCommand;
        if (partCommand.substr(0,3) == "lef"){
            if (cur->moveBlock(-1,0,repeat)){
                if (cur == &p1) {
                    cur  = &p2;
                } else {
                    cur = &p1;
                }
            }
        } else if (partCommand.substr(0,2) == "ri"){
            if (cur->moveBlock(1,0,repeat)){
                if (cur == &p1) {
                    cur  = &p2;
                } else {
                    cur = &p1;
                }
            }
        } else if (partCommand.substr(0,2) == "do"){
            if (cur->moveBlock(0,1,repeat)){
                if (cur == &p1) {
                    cur  = &p2;
                } else {
                    cur = &p1;
                }
            }
        } else if (partCommand.substr(0,2) == "cl"){
            if (cur->rotateBlock(0,repeat)){
                if (cur == &p1) {
                    cur  = &p2;
                } else {
                    cur = &p1;
                }
            }
        } else if (partCommand.substr(0,2) == "co"){
            if (cur->rotateBlock(1,repeat)){
                if (cur == &p1) {
                    cur  = &p2;
                } else {
                    cur = &p1;
                }
            }
        } else if (partCommand.substr(0,2)  == "dr"){
            cur->dropBlock();
            if (cur == &p1) {
                cur  = &p2;
            } else {
                cur = &p1;
            }
        } else if (partCommand.substr(0,6)  == "levelu"){
            cur->levelUpDown(1,repeat);
        } else if (partCommand.substr(0,6)  == "leveld"){
            cur->levelUpDown(-1,repeat);
        } else if (partCommand.substr(0,1)  == "n"){ //norandom file
            string file;
            cin >> file;
            //ifstream sor = ifstream{file};
            cur->switchRandom(file);
        } else if (partCommand.substr(0,2)  == "ra"){ //set back to random
            cur->switchRandom("");
        } else if (partCommand.substr(0,2)  == "se"){ //sequence file
            string file;
            cin >> file;
            fileInput = ifstream{file};
            useFile = true;
        } else if (partCommand.substr(0,2)  == "re"){
            restartGame();
            cur = &p1;
        } else if (partCommand  == "I" || partCommand  == "J" || partCommand  == "L"
                   || partCommand  == "O" || partCommand  == "Z" || partCommand  == "S" ||
                   partCommand  == "T"){
            cur->mutateBlock(partCommand[0]);
        } else if (partCommand.substr(0,2)  == "sk"){
            // skips the current block for extra feature
            if (cur->getScorePtr()->getCurScore() > (cur->getCurLev() +5)) {
                cur->getScorePtr()->addCurScore(-1*(cur->getCurLev() +5));
                cout << "Skipped current block and deducted: " << cur->getCurLev()+5 << " points" <<endl;
                cur->skipBlock();
            } else{
                cout << "Not enough score points to reduce" << endl;
            }
        } else {
            cout << "Invalid Command" << endl;
        }
        // check endGame
        if (p1.getEndGame() || p2.getEndGame()){
            view.showText(&p1,&p2);
            cout << "Game ended" << endl;
            endGame();
            break;
        }
    }
}

