#include "Node.h"
Node::Node() {
  this->create_board();
  player=1;
  value=0;
}

Node::Node(Node n, int c, int p) {
  player = p;
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
std::list<Node*> Node::getChildren() {
  return children;
}
int Node::getColumn() const{
  return column;
}

/*set Value*/
void Node::setValue(int v) {
  value = v;
}
void Node::addChild(Node* child) {
  children.push_back(child);
}
int Node::evaluationBoard() {
  //std::cout << "new" << std::endl;
  //this->print_board();
  int board_score = 0;
  for (int i=5; i>-1; i--) {
    unsigned int start_h=0;
    unsigned int end_h=3;
    for (; start_h < 4 && end_h < 7; start_h++, end_h++) {
      //std::cout << "Bowned : " << start_h << " ANOTHER: " << end_h << std::endl;
      unsigned int player_pieces=0;
      unsigned int ai_pieces=0;
      unsigned int open_space =0;
      for (unsigned int j=start_h; j<end_h; j++) {
        if (board[j][i] == 1) { ai_pieces++; }
        else if (board[j][i] == -1) { player_pieces++; }
        else { open_space++; }
      }
      if (ai_pieces == 1 && open_space == 2) { board_score+= 2; }
      else if (ai_pieces == 2 && open_space == 1) { board_score+= 5; }
      else if (ai_pieces == 3 && open_space == 0) { board_score+= 10; }
      else if (ai_pieces == 4 && open_space == 0) { board_score+= 10000; }
      else if (player_pieces == 1 && open_space == 2) { board_score+= -1; }
      else if (player_pieces == 2 && open_space == 1) { board_score+= -12; }
      else if (player_pieces == 3 && open_space == 0) { board_score+= -1000; }
      //std::cout << player_pieces << " " << ai_pieces << " " << open_space << std::endl;
      //std::cout << (player_pieces == 1) << " " << (open_space == 3) << std::endl;
      if(player_pieces == 1 && open_space == 3) {
        //std::cout << "EVAL: " << board_score << std::endl;
      }
    }
  }
  return board_score;
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
int Node::numCol_open() {
  int openCol = 0;
  for(unsigned int i=0; i<7; i++) {
    if(board[i][0] == 0) { openCol++; }
  }
  return openCol;
}
void Node::copy_board(int** b) {
  board = new int* [7];
  for(unsigned int i=0; i<7; i++) {
    board[i] = new int[6];
    for(unsigned int j=0; j<6; j++) {
      board[i][j] = b[i][j];
    }
  }
  for(int j=5; j>-1; j--) {
    if (board[column][j] == 0) {
      board[column][j] = player;
      row = j;
      break;
    }
  }
}
void Node::print_board() {
  std::cout << "-----------------------" << std::endl;
  for(int i=0; i<6; i++) {
    std::cout << "|";
    for(int j=0; j<7; j++) {
      if(board[j][i] == -1) { std::cout << " X "; }
      else if(board[j][i] == 1) { std::cout << " O "; }
      else { std::cout << " * "; }
    }
    std::cout << "|\n";
  }
  std::cout << "-----------------------\n|                     |\n___                 ___\n" << std::endl;
}
