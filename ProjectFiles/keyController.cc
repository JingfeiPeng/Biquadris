#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <sstream>
#include <string>
#include "keyController.h"
#define XK_CCLOCK 30
#define XK_CLOCK 31
#define XK_DROP 65
#define XK_DOWN 45
#define XK_LEFT 44
#define XK_RIGHT 46
#define XK_LEVUP 21
#define XK_LEVDOWN 20
#define XK_RESTART 27
#define XK_EXIT 26
#define XK_SKIP 64
#define XK_RANDOM 0x09
#define XK_BLIND 56
#define XK_HEAVY 43

using namespace std;


KeyController::KeyController(bool graphic, int level,string filename1,string filename2):
        graphic{graphic},level{level},view{View(graphic)},scoreP1{Score(level,&view,100,120)},scoreP2{Score(level,&view,540,120)},p1{BoardManager(level,filename1,&scoreP1,&view,100,120)},p2{BoardManager(level,filename2, &scoreP2,&view,540,120)}{}

void KeyController::restartGame(){
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

void KeyController::resetGame(){
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

void KeyController::askSpecialAction(BoardManager* target){
    cout << "Choose a special action by press either:" << endl;
    cout << "b for blind\nh for heavy" << endl;
    while (true) {
        int keycode = view.getPollEvent();
        if (keycode == XK_BLIND){
            target->showBlind();
            view.showText(&p1,&p2);
            break;
        } else if (keycode == XK_HEAVY) {
            target->setSpecialHeavy();
            view.showText(&p1,&p2);
            break;
        } else {
            cout << "Please press a valid key.\nChoose a special action by press either:" << endl;
            cout << "b for blind\nh for heavy" << endl;
        }
    }
}

void KeyController::endGame(){
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
    cout << "Press r to Reset Game and e to endGame" << endl;
    int keycode = view.getPollEvent();
    while(true) {
        if (keycode == XK_RESTART){
            runGame();
            break;
        } else if (keycode == XK_EXIT){
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
            cout << "Press any key to quit" << endl;
            keycode = view.getPollEvent();
            break;
        } else {
            cout << "Invalid command\nPress r to Reset Game and e to endGame" << endl;
            keycode = view.getPollEvent();
        }
    }
}

void KeyController::runGame(){
    BoardManager *cur = &p1;
    int keycode;
    while (true){
        //check if specialAction activated
        view.showText(&p1,&p2);
        if (p1.getSpecialAction()){
            askSpecialAction(&p2);
            p1.unsetSpecialAction();
        } else if (p2.getSpecialAction()){
            askSpecialAction(&p1);
            p2.unsetSpecialAction();
        }
        keycode = view.getPollEvent();
        if (keycode == XK_LEFT){
            if (cur->moveBlock(-1,0,1)){
                if (cur == &p1) {
                    cur  = &p2;
                } else {
                    cur = &p1;
                }
            }
        } else if (keycode == XK_RIGHT){
            if (cur->moveBlock(1,0,1)){
                if (cur == &p1) {
                    cur  = &p2;
                } else {
                    cur = &p1;
                }
            }
        } else if (keycode == XK_DOWN){
            if (cur->moveBlock(0,1,1)){
                if (cur == &p1) {
                    cur  = &p2;
                } else {
                    cur = &p1;
                }
            }
        } else if (keycode == XK_CLOCK){
            if (cur->rotateBlock(0,1)){
                if (cur == &p1) {
                    cur  = &p2;
                } else {
                    cur = &p1;
                }
            }
        } else if (keycode == XK_CCLOCK){
            if (cur->rotateBlock(1,1)){
                if (cur == &p1) {
                    cur  = &p2;
                } else {
                    cur = &p1;
                }
            }
        } else if (keycode  == XK_DROP){
            cur->dropBlock();
            if (cur == &p1) {
                cur  = &p2;
            } else {
                cur = &p1;
            }
        } else if (keycode == XK_LEVUP){
            cur->levelUpDown(1,1);
        } else if (keycode == XK_LEVDOWN){
            cur->levelUpDown(-1,1);
        } else if (keycode == XK_RESTART){
            restartGame();
         } else if (keycode == XK_SKIP){
            // skips the current block for extra feature
            if (cur->getScorePtr()->getCurScore() > (cur->getCurLev() +5)) {
                cur->getScorePtr()->addCurScore(-1*(cur->getCurLev() +5));
                cout << "Skipped current block and deducted: " << cur->getCurLev()+5 << " points" <<endl;
                cur->skipBlock();
            } else{
                cout << "Not enough score points to reduce" << endl;
            }
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



