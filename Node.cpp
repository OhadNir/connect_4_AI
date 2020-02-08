#include "Node.h"
Node::Node() {
  this->create_board();
}

Node::Node(Node n, int c, int r, int p) {
  player = p;
  row = r;
  column = c;
  copy_board(n.getBoard());
}

/*Get Functions*/
int** Node::getBoard() {
  return board;
}
int Node::getValue() const {
  return value;
}
int Node::getPlayer() const {
  return player;
}
std::list<Node> Node::getChildren() {
  return children;
}
int Node::getColumn() const{
  return column;
}

/*set Value*/
void Node::setValue(int v) {
  value = v;
}
int Node::evaluationBoard() {
  /*evalulates board value*/
}
void Node::create_board() {
  board = new int* [7];
  for(unsigned int i=0; i<7; i++) {
    board[i] = new int[6];
    for(unsigned int j=0; j<6; j++) {
      board[i][j] = 0;
    }
  }
}
void Node::copy_board(int** b) {
  board = new int* [7];
  for(unsigned int i=0; i<7; i++) {
    board[i] = new int[6];
    for(unsigned int j=0; j<6; j++) {
      board[i][j] = b[i][j];
    }
  }
  board[column][row] = player;
}
void Node::print_board() {
  std::cout << "-----------------------" << std::endl;
  for(int i=0; i<6; i++) {
    std::cout << "|";
    for(int j=0; j<7; j++) {
      if(board[j][i] == 1) { std::cout << " X "; }
      else if(board[j][i] == -1) { std::cout << " O "; }
      else { std::cout << " * "; }
    }
    std::cout << "|\n";
  }
  std::cout << "-----------------------\n|                     |\n___                 ___\n" << std::endl;
}
