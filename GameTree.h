#ifndef GAMETREE_H
#define GAMETREE_H
#include <iostream>
#include <cstdlib>
#include "Node.h"

class GameTree {
  public:
    /*Constructor*/
    GameTree(int);

    /*Public Member Functions*/
    long NumberOfBoardsGenerated();
    long NumberOfBoardsAnalyzed();
    long NumberOFMoves();
    long NumberOfWinStatesPY();
    long NumberOfWinStatesAI();

    int minimax(Node&, int, int, int, int);
    bool playerMove(int);
    void aiMove();
    void printGameSate();
    int WinDraw();
    int suggestMove();

  private:
    /*Private Member Functions*/
    void generateTree(Node&, int, int);
    void setNewGameState(int);
    void del(Node&);

    /*Private Member Varables*/
    Node root;
    int treedepth;
    long boardsGenerated = 0;
    long boardsAnalyzed = 0;
    long numberOfMoves = 0;
    long numberOfWinStatesPY = 0;
    long numberOfWinStatesAI = 0;

};

#endif
