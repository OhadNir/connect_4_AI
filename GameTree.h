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
    int minimax(Node&, int, int, int, bool);
    bool move(int);
    void printGameSate();


  private:
    /*Private Member Functions*/
    void generateTree(Node&, int, bool);

    /*Private Member Varables*/
    Node root;
};

#endif
