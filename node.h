#infdef NODE_H
#define NODE_H
#include <iostream>
#include <cstdlib>
#include <list>

class Node {
  public:
    /*Constructor*/
    Node(int**, int&, int&, int&);

    /*Get Functions*/
    int** getBoard() const;
    int getValue() const;
    int getPlayer() const;

    /*set Value*/
    void setValue(int);

  private:
    /*Member Functions*/
    int** copy_board(int**&, int&, int&);

    /*Member Varables*/
    int** board;
    int node_value;
    int column_played;
    int row_played;
    int player;
    std::list<Node> children;
};

#endif
