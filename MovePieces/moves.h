#ifndef MOVES_H
#define MOVES_H
#include "pawn_moves.h"
#include "knight_moves.h"
#include "rook_moves.h"
#include "bishop_moves.h"
#include "queen_moves.h"
#include "king_moves.h"

std::vector<MoveDet> get_all_moves(Piece p);

std::vector<MoveDet> all_legal_moves(bool color) {
  std::vector<MoveDet> mv(0), aux(0);
  if (color == BLACK) {
    for(long unsigned int i = 0; i < b->pieces_black.size(); i++) {
      if (b->pieces_black[i].type != NONE) {
        aux = get_all_moves(b->pieces_black[i]);
        mv.insert(mv.end(), aux.begin(), aux.end());
      }
    }
  }
  if (color == WHITE) {
    for(long unsigned int i = 0; i < b->pieces_white.size(); i++) {
      if (b->pieces_white[i].type != NONE) {
        aux = get_all_moves(b->pieces_white[i]);
        mv.insert(mv.end(), aux.begin(), aux.end());
      }
    }
  }
  return mv;
}
std::vector<MoveDet> get_all_moves(Piece p) {
    std::vector<MoveDet> mv;
    if (p.color == BLACK) {
        switch (p.type) {
            case PAWN_B:
                mv = get_moves_pawn_black(p);
                break;
            case ROOK_B:
                mv = get_moves_rook(p);
                break;
            case KNIGHT_B:
                mv = get_moves_knight(p);
                break;
            case BISHOP_B:
                mv = get_moves_bishop(p);
                break;
            case QUEEN_B:
                mv = get_moves_queen(p);
                break;
            case KING_B:
                mv = get_moves_king(p);
                break;
            default:
                break;
        }
    } else if (p.color == WHITE) {
        switch (p.type) {
            case PAWN_W:
                mv = get_moves_pawn_white(p);
                break;
            case ROOK_W:
                mv = get_moves_rook(p);
                break;
            case KNIGHT_W:
                mv = get_moves_knight(p);
                break;
            case BISHOP_W:
                mv = get_moves_bishop(p);
                break;
            case QUEEN_W:
                mv = get_moves_queen(p);
                break;
            case KING_W:
                mv = get_moves_king(p);
                break;
            default:
                break;
        }
    }
    return mv;
}
#endif
