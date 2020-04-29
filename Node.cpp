#include "Node.h"
Node::Node() {
  this->create_board();
  player=1;
  value=0;
  gameOver = false;
}

Node::Node(Node n, int c, int p) {
  player = p;
  column = c;
  copy_board(n.getBoard());
  gameOver = false;
}
Node::~Node() {
  this->del();
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
  int board_score = 0;

  /*Horizontal*/
  for (int i=5; i>-1; i--) {
    int start_h=0;
    int end_h=3;
    for (; start_h < 4 && end_h < 7; start_h++, end_h++) {
      unsigned int player_pieces=0;
      unsigned int ai_pieces=0;
      unsigned int open_space =0;
      for (int j=start_h; j<end_h+1; j++) {
        if (board[j][i] == 1) { ai_pieces++; }
        else if (board[j][i] == -1) { player_pieces++; }
        else { open_space++; }
      }
      board_score += scoring(ai_pieces, player_pieces, open_space);
    }
  }

  /*Vertical*/
  for (int i=0; i<7; i++) {
    int start_v=2;
    int end_v=5;
    for (; start_v > -1 && end_v > 2; start_v--, end_v--) {
      unsigned int player_pieces=0;
      unsigned int ai_pieces=0;
      unsigned int open_space =0;
      for (int j=end_v; j>start_v-1; j--) {
        if (board[i][j] == 1) { ai_pieces++; }
        else if (board[i][j] == -1) { player_pieces++; }
        else { open_space++; }
      }
      board_score += scoring(ai_pieces, player_pieces, open_space);
    }
  }

  /*Diagonal Left*/
  for (int t=0; t<4; t++) {
    int start_h = t;
    int end_h = t+3;
    int start_v = 2;
    int end_v = 5;
    for (; start_v > -1 && end_v > 2; start_v--, end_v--) {
      unsigned int player_pieces=0;
      unsigned int ai_pieces=0;
      unsigned int open_space =0;
      int i = start_h;
      for (int j=start_v; j < end_v+1 && i < end_h+1; j++, i++) {
        if (board[i][j] == 1) { ai_pieces++; }
        else if (board[i][j] == -1) { player_pieces++; }
        else { open_space++; }
      }
      board_score += scoring(ai_pieces, player_pieces, open_space);
    }
  }

  /*Diagonal right*/
  for (int t=6; t>2; t--) {
    int start_h = t;
    int end_h = t-3;
    int start_v = 2;
    int end_v = 5;
    for (; start_v > -1 && end_v > 2; start_v--, end_v--) {
      unsigned int player_pieces=0;
      unsigned int ai_pieces=0;
      unsigned int open_space =0;
      int i = start_h;
      for (int j=start_v; j < end_v+1 && i > end_h-1; j++, i--) {
        if (board[i][j] == 1) { ai_pieces++; }
        else if (board[i][j] == -1) { player_pieces++; }
        else { open_space++; }
      }
      board_score += scoring(ai_pieces, player_pieces, open_space);
    }
  }

  return board_score;
}
int Node::scoring(int ai, int player, int blank) {
  int score = 0;
  if (ai == 1 && blank == 3) { score+= 2; }
  else if (ai == 2 && blank == 2) { score+= 6; }
  else if (ai == 3 && blank == 1) { score+= 12; }
  else if (ai == 4 && blank == 0) { score+= 100000; }
  else if (player == 1 && blank == 3) { score+= -1; }
  else if (player == 2 && blank == 2) { score+= -6; }
  else if (player == 3 && blank == 1) { score+= -1000; }
  else if (player == 4 && blank == 0) { score+= -100000; }
  return score;
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
  std::cout << "\t-----------------------" << std::endl;
  for(int i=0; i<6; i++) {
    std::cout << "\t|";
    for(int j=0; j<7; j++) {
      if(board[j][i] == -1) { std::cout << " X "; }
      else if(board[j][i] == 1) { std::cout << " O "; }
      else { std::cout << " * "; }
    }
    std::cout << "|\n";
  }
  std::cout << "\t-----------------------\n\t|                     |\n\t___                 ___\n" << std::endl;
}
void Node::del() {
  //std::cout << "Distructor is called." << std::endl;
  // for (int i=0; i<7; i++) {
  //   delete board[i];
  // }
  // delete board;
}
