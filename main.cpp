#include <string>
#include <signal.h>
#include <bits/stdc++.h>
#include "board.h"
#include "functions.h"
#include "./PieceClasses/piece.h"
#include "./MovePieces/moves.h"
#include "reply.h"

int main() {
  std::ofstream fout;
  fout.open("out.txt");
  signal(SIGINT, SIG_IGN);
  std::cout << "\n";
  std::string xboard_command;
  std::string first_command;
  std::string delimiter = " ";
  Board* b = Board::getBoard();
  b->showBoard();
  int round = 0;
  while (true) {
    fflush(stdout);
    std::getline(std::cin, xboard_command);
    first_command = xboard_command.substr(0, xboard_command.find(delimiter));
    if(xboard_command.compare("xboard") == 0) {
        fout << xboard_command << std::endl;
        continue;
    } else if (first_command.compare("protover") == 0) {
        fout << xboard_command << std::endl;
        continue;
    } else if (xboard_command.compare("random") == 0) {
        fout << xboard_command << std::endl;
        continue;
    } else if (first_command.compare("level") == 0) {
        fout << xboard_command << std::endl;
        continue;
    } else if (xboard_command.compare("post") == 0) {
        fout << xboard_command << std::endl;
        continue;
    } else if (xboard_command.compare("hard") == 0) {
        fout << xboard_command << std::endl;
        continue;
    } else if (first_command.compare("time") == 0) {
        fout << xboard_command << std::endl;
        continue;
    } else if (first_command.compare("otim") == 0) {
        fout << xboard_command << std::endl;
        continue;
    } else if (xboard_command.compare("new") == 0) {
        fout << xboard_command << std::endl;
        new_command();
        continue;
    } else if (first_command.compare("force") == 0) {
        fout << first_command << std::endl;
        force_command();
        continue;
    } else if (first_command.compare("go") == 0) {
        fout << first_command << std::endl;
        // the bot will execute a command depending on the colour
        go_command();
        continue;
    } else if (first_command.compare("white") == 0) {
        fout << first_command << std::endl;
         white_command(); // execute white command
        continue;
    } else if (first_command.compare("black") == 0) {
        fout << first_command << std::endl;
       black_command();
       continue;
    } else if (first_command.compare("quit") == 0) {
        fout << first_command << std::endl;
        //quit_command();
        continue;
    } else if (first_command.compare("resign") == 0) {
        fout << first_command << std::endl;
        resign_command();
        continue;
    } else if (first_command.compare("sd") == 0){
        continue;
    } else {
        fout << xboard_command << std::endl;
        // calculate old and new lines and coloumns for the move from board
        int old_col = xboard_command.at(0) - 'a' + 1;
        int old_line = xboard_command.at(1) - '0';
        int new_col = xboard_command.at(2) - 'a' + 1;
        int new_line = xboard_command.at(3) - '0';
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
        // execute castling:
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
        if (round == 0 && b->getColorBot() == BLACK) {
            if (old_line == 2 && new_line == 4) {
                if (old_col == 5) {
                    std::cout << "move " << 'c' << 7 << 'c' << 5 << std::endl;
                    MoveDet mv(7, 3, 5, 3, PAWN_B);
                    b->apply(mv);
                } else if (old_col == 4) {
                    std::cout << "move " << 'd' << 7 << 'd' << 5 << std::endl;
                    MoveDet mv(7, 4, 5, 4, PAWN_B);
                    b->apply(mv);
                } else {
                    reply();
                }
            } else {
                reply();
            }
        } else {
            reply();
        }
        round++;
    }
    xboard_command.clear();
    first_command.clear();
  }
  fout.close();
    // adversarul e jos, noi suntem sus
    return 0;
}
