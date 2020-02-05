#infdef GAMETREE_H
#define GAMETREE_H
#include <iostream>
#include <cstdlib>
#include "Node.h"

class GameTree {
  public:
    /*Constructor*/
    GameTree();
    void evaluation_board(int** &);
    int minimax(Node&, int, int, int, bool);
    void move(int);

  private:
    /*Member Functions*/
    Node generateTree();
    /*Member Varables*/
    Node root;
};

#endif
