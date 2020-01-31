#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <cstdlib>
#include <list>
#include "board.h"

class Node {
  public:
  /*Class constructor/Destracor*/
  Node(bool p);
  Node(Board b, int c, bool p);
  ~Node() {this->del();}

  /*Public Class Functions*/
  int calculate_move_value();
  Board get_board_obj();
  int get_value();
  Node* get_parent();
  std::list<Node*> get_children();
  void add_child(Node* n);
  void assign_parent(Node* n);

  /*Board functions*/
  int** get_board();
  void print_board();
  bool set_val_index(int column, bool player_type);
  unsigned int num_open_col();

  std::list<Node*>::iterator child_begin();
  std::list<Node*>::iterator child_end();

  private:
  /*Private Class Variables*/
  std::list<Node*> children;
  Node* parent;
  Board board;
  int value;
  int column;
  bool player;

  /*Private Class Variables*/
  void del();
};

Node::Node(bool p) {
  parent = NULL;
  board = Board();
  value = 1010; //special void value;
  column = 1010; //special void value;
  player = p;
}
Node::Node(Board b, int c, bool p) {
  parent = NULL;
  board = Board(b.get_board());
  value = 1010; //special void value;
  column = c;
  player = p;
  set_val_index(c, p);
}
void Node::del() {
  /*Destracor*/
}
std::list<Node*>::iterator Node::child_begin() {
  return children.begin();
}
std::list<Node*>::iterator Node::child_end() {
  return children.end();
}

int Node::calculate_move_value() {
  /*Calculates move value*/
}
Board Node::get_board_obj() {
  return board;
}
int Node::get_value() {
  return value;
}
Node* Node::get_parent() {
  return parent;
}
std::list<Node*> Node::get_children() {
  return children;
}
void Node::print_board() {
  board.print_board();
}
void Node::add_child(Node* n) {
  children.push_back(n);
  n->assign_parent(this);
}
void Node::assign_parent(Node* n) {
  parent = n;
}
int** Node::get_board() {
  return board.get_board();
}
bool Node::set_val_index(int column, bool player_type) {
  return board.set_val_index(column, player_type);
}
unsigned int Node::num_open_col() {
  return board.num_open_col();
}
#endif
