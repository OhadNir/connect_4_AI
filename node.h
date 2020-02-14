#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <cstdlib>
#include <list>

class Node {
  public:
    /*Defult Constructor*/
    Node();
    /*Constructor*/
    Node(Node, int, int);

    /*Get Functions*/
    int getValue() const;
    int getPlayer() const;
    int getColumn() const;
    int** getBoard();
    std::list<Node*> getChildren();

    /*set Value*/
    void setValue(int);
    void addChild(Node*);

    /*Functions*/
    int evaluationBoard();
    void print_board();
    int numCol_open();


  private:
    /*Private Member Functions*/
    void create_board();
    void copy_board(int**);

    /*Private Member Varables*/
    int** board;
    int value;
    int column;
    int row;
    int player;
    std::list<Node*> children;
};

#endif
