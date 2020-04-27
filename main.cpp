#include <iostream>
#include <cstdlib>
#include "GameTree.h"
#include "Node.h"

int main() {
  std::cout << "Welcome Connect-4!" << std::endl;
  std::cout << "How many moves ahead will the AI look? (NOTICE: 4 will be ideal for most machines. Any more could make the AI take a long time to make a decision.)" << std::endl;
  int depth;
  std::cin >> depth;

  std::cout << "Would you like Suggestions ON(1) or OFF(any other number)? (Won't guarantee a win; However, it will suggest optimal moves to consider.)" <<std::endl;
  int cheats = 0;
  std::cin >> cheats;

  bool suggest = false;
  if (cheats == 1) {
    suggest = true;
  }
  GameTree game = GameTree(depth);
  bool player = true;

  std::cout << "Player moves first." << std::endl;
  while(true) {
    if (game.WinDraw() != -1) {
      game.printGameSate();
      break;
    }
    if (player) {
      while(true) {
        game.printGameSate();
        std::cout << "Choose a column between 1 and 7..." << std::endl;
        if (suggest) {
          std::cout << "AI recommends for you to play column: " << game.suggestMove() << std::endl;
        }
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

  if(game.WinDraw() == 0) {
    std::cout << "Draw!" << std::endl;
  }
  else if(game.WinDraw() == 1) {
    std::cout << "Player Wins!" << std::endl;
  }
  else {
    std::cout << "AI Wins!" << std::endl;
  }
  std::cout << "Game Statistic:\n" <<
               "Total Number of Moves Made - " << game.NumberOFMoves() << "\n" <<
               "Board States Generated - " << game.NumberOfBoardsGenerated() << "\n"<<
               "Boards Analyzed - " << game.NumberOfBoardsAnalyzed() << "\n" <<
               "Player Win States Within " << depth << " moves - " << game.NumberOfWinStatesPY() << "\n" <<
               "AI Win States Within " << depth << " moves - " << game.NumberOfWinStatesAI() <<
               std::endl;

  return 0;
}
