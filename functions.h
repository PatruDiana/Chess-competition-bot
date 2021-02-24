#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "./MovePieces/moves.h"
#include "resign.h"
#include "reply.h"
#include <bits/stdc++.h>
void white_command();
void black_command();
void analyse_command();

void new_command() {
    Board* b = Board::getBoard();
    b->reset_board();   // initial configuration
}

void force_command() {
  std::string command, first_command, second_command;
  std::ofstream out;
  Board* b = Board::getBoard();
    out.open("force_out.txt");
    while(1) { // read commands continuously
      fflush(stdout);
      std::getline(std::cin, command);
      first_command = command.substr(0, command.find(" "));
      out << command << "\n";
      if (command.compare("white") == 0) {
        white_command();
        return;
      } else if (command.compare("black") == 0) {
        black_command();
        return;
      } else if (command.compare("analyze") == 0) {
        analyse_command();
        std::getline(std::cin, command);
      } else if (command.compare("new") == 0) {
        new_command();
        return;
    } else if (command.compare("computer") == 0){
        continue;
    } else if(first_command.compare("ping") == 0) {
        second_command = command.substr(5);
        std::cout << "pong " << second_command << "\n";
        continue;
    } else {  //execute the moves
        int old_col = command.at(0) - 'a' + 1,
            old_line = command.at(1) - '0',
            new_col = command.at(2) - 'a' + 1,
            new_line = command.at(3) - '0';
            MoveDet mv(old_line, old_col, new_line, new_col, b->getBoardConfig(old_line, old_col).type);
            Piece p = b->getBoardConfig(old_line, old_col);
            if (p.type == PAWN_W) {
                Piece other = b->getBoardConfig(new_line, new_col);
                if (other.type == NONE && new_line == old_line + 1
                    && (new_col == old_col + 1 || new_col == old_col - 1)) {
                        Piece none(old_line, new_col);
                        Piece neighbour = b->getBoardConfig(old_line, new_col);
                        b->boardConfig[mv.old_line][mv.new_col] = none;
                        b->update_attack(neighbour);
                }
            } else if (p.type == PAWN_B) {
                Piece other = b->getBoardConfig(new_line, new_col);
                if (other.type == NONE && new_line == old_line - 1
                    && (new_col == old_col + 1 || new_col == old_col - 1)) {
                        Piece none(old_line, new_col);
                        Piece neighbour = b->getBoardConfig(old_line, new_col);
                        b->boardConfig[mv.old_line][mv.new_col] = none;
                        b->update_attack(neighbour);
                }
            }
            b->apply(mv);
            b->update_pawn_promotion(p, new_line, new_col);
            if (old_line == 1 && new_line == 1) {
                if (old_col == 5 && new_col == 7) {
                    MoveDet mv(1, 8, 1, 6, b->getBoardConfig(1, 8).type);
                    b->apply(mv);
                } else if (old_col == 5 && new_col == 3) {
                    MoveDet mv(1, 1, 1, 4, b->getBoardConfig(1, 1).type);
                    b->apply(mv);
                }
            } else if (old_line == 8 && new_line == 8) {
                if (old_col == 5 && new_col == 7) {
                    MoveDet mv(8, 8, 8, 6, b->getBoardConfig(8, 8).type);
                    b->apply(mv);
                } else if (old_col == 5 && new_col == 3) {
                    MoveDet mv(8, 1, 8, 4, b->getBoardConfig(8, 1).type);
                    b->apply(mv);
                }
            }
         b->showBoard();
      }
      command.clear();
    }
}

void analyse_command() {
    Board* b = Board::getBoard();
    std::string xboard_command;
    // std::ofstream out;
    // out.open("force_out.txt");
    while (true) {
        fflush(stdout);
        std::getline(std::cin, xboard_command);
        if (xboard_command.compare(".") == 0) {
          continue;
        } else if (xboard_command.compare("exit") == 0) {
            return; // finish when found exit
        } else { // do move
            int old_col = xboard_command.at(0) - 'a' + 1,
                old_line = xboard_command.at(1) - '0',
                new_col = xboard_command.at(2) - 'a' + 1,
                new_line = xboard_command.at(3) - '0';
                MoveDet mv(old_line, old_col, new_line, new_col, b->getBoardConfig(old_line, old_col).type);
                Piece p = b->getBoardConfig(old_line, old_col);
                if (p.type == PAWN_W) {
                    Piece other = b->getBoardConfig(new_line, new_col);
                    if (other.type == NONE && new_line == old_line + 1
                        && (new_col == old_col + 1 || new_col == old_col - 1)) {
                            Piece none(old_line, new_col);
                            Piece neighbour = b->getBoardConfig(old_line, new_col);
                            b->boardConfig[mv.old_line][mv.new_col] = none;
                            b->update_attack(neighbour);
                    }
                } else if (p.type == PAWN_B) {
                    Piece other = b->getBoardConfig(new_line, new_col);
                    if (other.type == NONE && new_line == old_line - 1
                        && (new_col == old_col + 1 || new_col == old_col - 1)) {
                            Piece none(old_line, new_col);
                            Piece neighbour = b->getBoardConfig(old_line, new_col);
                            b->boardConfig[mv.old_line][mv.new_col] = none;
                            b->update_attack(neighbour);
                    }
                }
                b->apply(mv);
                b->update_pawn_promotion(p, new_line, new_col);
                if (old_line == 1 && new_line == 1) {
                    if (old_col == 5 && new_col == 7) {
                        MoveDet mv(1, 8, 1, 6, b->getBoardConfig(1, 8).type);
                        b->apply(mv);
                    } else if (old_col == 5 && new_col == 3) {
                        MoveDet mv(1, 1, 1, 4, b->getBoardConfig(1, 1).type);
                        b->apply(mv);
                    }
                } else if (old_line == 8 && new_line == 8) {
                    if (old_col == 5 && new_col == 7) {
                        MoveDet mv(8, 8, 8, 6, b->getBoardConfig(8, 8).type);
                        b->apply(mv);
                    } else if (old_col == 5 && new_col == 3) {
                        MoveDet mv(8, 1, 8, 4, b->getBoardConfig(8, 1).type);
                        b->apply(mv);
                    }
                }
            b->showBoard();
        }
    xboard_command.clear();
    }
}

void go_command() {
  Board *b = Board::getBoard();
  // move the pawn on the suitable color
 reply();
  b->showBoard();
}

void black_command() {
    Board *b = Board::getBoard();
    std::string xboard_command;
    std::string first_command;
    std::string delimiter = " ";
    while (true) {
      fflush(stdout);
      std::getline(std::cin, xboard_command);
      first_command = xboard_command.substr(0, xboard_command.find(delimiter));
      if (first_command.compare("time") == 0) {
        continue;
      } else if (first_command.compare("otim") == 0) {
        continue;
      } else if (xboard_command.compare("go") == 0) {
        go_command();
        break;
      } else {
        b->flipBotWhite();
        break;
      }
    }
}

void white_command() {
    Board *b = Board::getBoard();
    std::string xboard_command;;
    std::string first_command;
    std::string delimiter = " ";
    while (true) {
      fflush(stdout);
      std::getline(std::cin, xboard_command);
      first_command = xboard_command.substr(0, xboard_command.find(delimiter));
      if (first_command.compare("time") == 0) {
        continue;
      } else if (first_command.compare("otim") == 0) {
        continue;
      } else {
        b->flipBotBlack();
        break;
      }
    }
}

void quit_command() {
    std::cout << "quit\n";
    //exit(1);
}
#endif
