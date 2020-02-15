#include <iostream>
#include <cstdlib>
#include "GameTree.h"
#include "Node.h"

int main() {
  std::cout << "Welcome Connect-4!" << std::endl;
  GameTree game = GameTree();
  bool player = true;

  std::cout << "Player moves first." << std::endl;
  while(true) {
    if (game.WinDraw()) {
      game.printGameSate();
      break;
    }
    if (player) {
      while(true) {
        game.printGameSate();
        std::cout << "Choose a column between 1 and 7..." << std::endl;
        int player_column;
        std::cin >> player_column;
        if (player_column-1 >= 0 && player_column-1 < 7 ) {
          bool valid_move = game.playerMove(player_column-1);
          if(valid_move) {
            game.printGameSate();
            player = false;
            break;
          }
          else {
            std::cout << "That Column is full!" << std::endl;
          }
        }
        else {
          std::cout << "Invalid Column!" << std::endl;
        }
      }
    }
    else {
      game.aiMove();
      player = true;
    }
  }

  return 0;
}
