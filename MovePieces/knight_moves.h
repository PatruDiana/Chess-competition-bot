#ifndef KNIGHT_MOVES_H
#define KNIGHT_MOVES_H
#include "../board.h"

std::vector<MoveDet> get_basic_knight(Piece p);
std::vector<MoveDet> get_attack_knight(Piece p);

std::vector<MoveDet> get_moves_knight(Piece p) {
    std::vector<MoveDet> mv, aux_mov;
    mv = get_basic_knight(p);
    aux_mov = get_attack_knight(p);
    mv.insert(mv.end(), aux_mov.begin(), aux_mov.end());
    return mv;
}
std::vector<MoveDet> get_basic_knight(Piece p) {
  std::vector<MoveDet> mv;
  int line = p.line, col = p.col;
  PieceType type = p.type;
  int x[8] = {2, 1, -1, -2, -2, -1,  1,  2};
  int y[8] = {1, 2,  2,  1, -1, -2, -2, -1};
  for (int i = 0; i < 8; i++) {
      Piece piece = b->getBoardConfig(line + x[i], col + y[i]);
      if (piece.type == NONE) { // empty cell
          MoveDet move(line, col, line + x[i], col + y[i], type);
          mv.push_back(move);
      }
  }
  return mv;
}
std::vector<MoveDet> get_attack_knight(Piece p) {
  std::vector<MoveDet> mv;
  int line = p.line, col = p.col;
  PieceType type = p.type;
  int x[8] = {2, 1, -1, -2, -2, -1,  1,  2};
  int y[8] = {1, 2,  2,  1, -1, -2, -2, -1};
  for (int i = 0; i < 8; i++) {
      Piece piece = b->getBoardConfig(line + x[i], col + y[i]);
      if (piece.color != p.color && piece.color != NO_COL) { // oponent
          MoveDet move(line, col, line + x[i], col + y[i], type);
          mv.push_back(move);
      }
  }
  return mv;
}
#endif
