#include "GameTree.h"

GameTree::GameTree() {
  //root = generateTree(Node);
}
int GameTree::minimax(Node& game, int depth, int alpha, int beta, bool player) {
  // if (depth == 0 || game.getChildren().size() == 0) {
  //   return game.evaluationBoard();
  // }
  // if (player) {
  //   int value = -1010;
  //   std::list<Node> children = game.getChildren();
  //   int temp = 0;
  //   for (std::list<Node>::iterator it = children.begin(); it!=children.end(); it++) {
  //     temp = minimax((*it), depth-1, alpha, beta, false);
  //     if (value < temp) { value = temp; }
  //     if (alpha > value) { alpha = value; }
  //     if (alpha >= beta) {
  //       break;
  //     }
  //   }
  //   n.setValue(value);
  //   return value;
  // }
  // else {
  //   int value = 1010;
  //   std::list<Node> children = game.get_children();
  //   int temp = 0;
  //   for (std::list<Node>::iterator it = children.begin(); it!=children.end(); it++) {
  //     temp = minimax((*it), depth-1, alpha, beta, true);
  //     if (value > temp) { value = temp; }
  //     if (beta < value) { beta = value; }
  //     if (alpha >= beta) {
  //       break;
  //     }
  //   }
  //   game.setValue(value);
  //   return value;
}
bool GameTree::move(int c) {
  bool found_column = false;
  std::list<Node> children = root.getChildren();
  for(std::list<Node>::iterator it = children.begin(); it != children.end(); it++) {
    if ((*it).getColumn() == c) {
      root = *it;
      found_column= true;
      break;
    }
  }
  return found_column;
}
void GameTree::printGameSate() {
  root.print_board();
}
void GameTree::generateTree(Node& game, int depth, bool player_turn) {
  /*generateTree*/
}
