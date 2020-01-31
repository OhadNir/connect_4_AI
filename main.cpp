#include <iostream>
#include <cstdlib>
#include <list>
#include "node.h"
#include "board.h"

const int MAXDEPTH = 2;

void generate_game_tree(Node& current_game_state, int depth, bool player_turn) {
  if(depth == 0 || current_game_state.num_open_col() == 0) {
    return;
  }
  Board b = current_game_state.get_board_obj();
  for(int i=0; i<7; i++) {
    if(b.get_board()[i][0] == 0) {
      Node* n = new Node(b, i, player_turn);
      current_game_state.add_child(n);
      if(player_turn) { generate_game_tree(*n, depth-1, false); }
      else { generate_game_tree(*n, depth-1, true); }
    }
  }

}

int main() {
  std::cout << "Welcome Connect-4!" << std::endl;

  while(true) {
    int temp = 0;
    std::cout << "Type '1' to play. Type '2' to get rule book." << std::endl;
    std::cin >> temp;
    if (temp == 1) {
      break;
    }
    else if (temp == 2) {
      /*print rulebook*/
      break;
    }
    else {
      std::cout << "Invalid input! Please try again." << std::endl;
    }
  }

  int player;
  while(true) {
    std::cout << "Pick your Player (player 1 goes first, player 2 goes second):" << std::endl;
    std::cin >> player;
    if (player == 1 || player == 2) {
      player = player-1;
      break;
    }
    else {
      std::cout << "That's not a valid player! Please type '1' to be player 1 and '2' to be player 2." << std::endl;
    }
  }

  bool players_turn;
  if (player == 0) {
    std::cout << "Player 1: Player vs. Player 2: AI\nPlayer goes first." << std::endl;
    players_turn = true;
  }
  else {
    std::cout << "Player 1: AI vs. Player 2: Player\nAI goes first." << std::endl;
    players_turn = false;
  }

  Node n = Node(players_turn);
  generate_game_tree(n, MAXDEPTH, players_turn);
  bool game_over = false;

  // while(!game_over) {
  //   if(players_turn) {
  //     Board current_board = Board();
  //     current_board.print_board();
  //     std::cout << "Choose a column between 1 and 7..." << std::endl;
  //     int player_column;
  //     std::cin >> player_column;
  //     bool success = current_board.set_val_index(player_column-1, players_turn);
  //     if (success) {
  //       current_board.print_board();
  //       // break;
  //     }
  //   }
  // }
  return 0;
}
