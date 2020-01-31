#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <cstdlib>

class Board {
  public:
  Board();
  Board(int** b);
  ~Board() {this->del();}


  int** get_board();
  void print_board();
  bool set_val_index(int column, bool player_type);
  unsigned int num_open_col();

  private:
  int** board;
  void create_board();
  void copy_board(int** b);
  void del();
};

Board::Board() {
  this->create_board();
}
Board::Board(int** b) {
  this->copy_board(b);
}
void Board::del() {
}
void Board::create_board() {
  board = new int* [7];
  for(int i=0; i<7; i++) {
    board[i] = new int[6];
    for(int j=0; j<6; j++) {
      board[i][j] = 0;
    }
  }
}
void Board::copy_board(int** b) {
  board = new int* [7];
  for(int i=0; i<7; i++) {
    board[i] = new int[6];
    for(int j=0; j<6; j++) {
      board[i][j] = b[i][j];
    }
  }
}
bool Board::set_val_index(int column, bool player_type) {
  if(column >= 0 && column <= 6) {
    int* c = board[column];
    if (c[0] == 0) {
      for (int i=5; i>-1; i--) {
        if(c[i] == 0) {
          if(player_type) { c[i] = 1; }
          else { c[i] = -1; }
          return true;
        }
      }
    }
    else {
      std::cout << "Column is Full!" << std::endl;
      return false;
    }
  }
  else {
    std::cout << "Invalid Column!" << std::endl;
    return false;
  }
}
unsigned int Board::num_open_col() {
  unsigned int open_columns = 7;
  for(int i=0; i<7; i++) {
    if (board[i][0] != 0) {
      open_columns--;
    }
  }
  return open_columns;
}
int** Board::get_board() {
  return board;
}
void Board::print_board() {
  std::cout << "-----------------------" << std::endl;
  for(int i=0; i<6; i++) {
    std::cout << "|";
    for(int j=0; j<7; j++) {
      if(board[j][i] == 1) { std::cout << " X "; }
      else if(board[j][i] == 1) { std::cout << " X "; }
      else if(board[j][i] == -1) { std::cout << " O "; }
      else { std::cout << " * "; }
    }
    std::cout << "|\n";
  }
  std::cout << "-----------------------\n|                     |\n___                 ___\n" << std::endl;
}
#endif
