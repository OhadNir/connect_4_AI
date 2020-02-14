#ifndef GAMETREE_H
#define GAMETREE_H
#include <iostream>
#include <cstdlib>
#include "Node.h"

class GameTree {
  public:
    /*Constructor*/
    GameTree();

    /*Public Member Functions*/
    int minimax(Node&, int, int, int, int);
    bool playerMove(int);
    void aiMove();
    void printGameSate();
    bool WinDraw();


  private:
    /*Private Member Functions*/
    void generateTree(Node&, int, int);

    /*Private Member Varables*/
    Node root;
};

#endif
