#include "GameTree.h"

int DEPTH = 5;

GameTree::GameTree() {
  root = Node();
  generateTree(root, DEPTH, 1);
}
int GameTree::minimax(Node& game, int depth, int alpha, int beta, int player) {
  if (depth == 0 || game.getChildren().size() == 0) {
    return game.getValue();
  }
  if (player == 1) {
    int value = -1000000;
    std::list<Node*> children = game.getChildren();
    int temp = 0;
    for (std::list<Node*>::iterator it = children.begin(); it!=children.end(); it++) {
      temp = minimax((**it), depth-1, alpha, beta, -1);
      if (value < temp) { value = temp; }
      if (alpha > value) { alpha = value; }
      if (alpha >= beta) {
        break;
      }
    }
    game.setValue(value);
    return value;
  }
  else {
    int value = 1000000;
    std::list<Node*> children = game.getChildren();
    int temp = 0;
    for (std::list<Node*>::iterator it = children.begin(); it!=children.end(); it++) {
      temp = minimax((**it), depth-1, alpha, beta, 1);
      if (value > temp) { value = temp; }
      if (beta < value) { beta = value; }
      if (alpha >= beta) {
        break;
      }
    }
    game.setValue(value);
    return value;
  }
}
bool GameTree::playerMove(int c) {
  bool found_column = false;
  std::list<Node*> children = root.getChildren();
  std::list<Node*>::iterator it = children.begin();
  for(; it != children.end(); it++) {
    if ((**it).getColumn() == c) {
      root = **it;
      generateTree(root, DEPTH, -1);
      minimax(root, DEPTH, -1010, 1010, 1);
      found_column= true;
      break;
    }
  }
  return found_column;
}
void GameTree::aiMove() {
  std::list<Node*> children = root.getChildren();
  std::list<Node*>::iterator it = children.begin();
  for (; it != children.end(); it++) {
    if (root.getValue() == (**it).getValue()) {
      root = (**it);
      generateTree(root, DEPTH, 1);
      break;
    }
  }
}
void GameTree::printGameSate() {
  root.print_board();
}
bool GameTree::WinDraw() {
  if(root.gameOver) {
    if(root.getValue() >= 5000) {
      std::cout << "AI Wins!" << std::endl;
      return true;
    }
    else if (root.getValue() <= -2500) {
      std::cout << "Player Wins!" << std::endl;
      return true;
    }
    else if (root.numCol_open() == 0) {
      std::cout << "Draw!" << std::endl;
      return true;
    }
  }
  return false;
}
void GameTree::generateTree(Node& game, int depth, int player) {
  int value = game.evaluationBoard();
  if(depth == 0 || game.numCol_open() == 0 || value >= 5000 || value <= -2500) {
    //std::cout << "value: " << value << std::endl;
    if (value >= 5000 || value <= -3000 || game.numCol_open() == 0) {
      //game.print_board();
      game.gameOver = true;
    }
    game.setValue(value);
    return;
  }
  if(game.getChildren().size() != 0) {
    std::list<Node*> possible_next_moves = game.getChildren();
    std::list<Node*>::iterator it = possible_next_moves.begin();
    for (; it != possible_next_moves.end(); it++) {
      if(player == 1) { generateTree(**it, depth-1, -1); }
      else{ generateTree(**it, depth-1, 1); }
    }
  }
  else {
    for(int i=0; i<7; i++) {
      if(game.getBoard()[i][0] == 0) {
        if(player == 1) {
          Node* n = new Node(game, i, -1);
          game.addChild(n);
          generateTree(*n, depth-1, -1);
        }
        else {
          Node* n = new Node(game, i, 1);
          game.addChild(n);
          generateTree(*n, depth-1, 1);
        }
      }
    }
  }
}
