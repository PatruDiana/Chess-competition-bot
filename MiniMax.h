#ifndef MINMAX_H
#define MINMAX_H
#include "board.h"
#include "./MovePieces/moves.h"
#include "resign.h"
#include "check_checkMate.h"
#include "resign.h"
#include <climits>
MoveDet best_move;
std::ofstream debug("debug_minmax.txt");
int maxi(int depth, bool bot_color, int beta);
int mini(int current_depth, bool color, int alfa);

MoveDet minimax(int depth) {
    if (b->getColorBot() == BLACK) {
        maxi(depth, b->getColorBot(), INT_MAX);
    } else {
        mini(depth, b->getColorBot(), INT_MIN);
    }
    return best_move;
}
int evaluate(bool color) {
      int current_score_bot = 0, current_score_opponent = 0;
      for (int i = 1; i < LEN; i++) {
        for (int j = 1; j < LEN; j++) {
          if (b->getBoardConfig(i, j).color == b->getColorBot()) {
              current_score_bot += b->getBoardConfig(i, j).score;
              current_score_bot += strategy_points(i, j, b->getColorBot());
            } else {
              current_score_opponent += b->getBoardConfig(i, j).score;
              current_score_opponent += strategy_points(i, j, !b->getColorBot());
            }
        }
      }
      return (current_score_bot - current_score_opponent);
}

int maxi(int current_depth, bool color, int beta) {
  if (current_depth == 0) {
    return evaluate(color);
  }
  int best = INT_MIN;
  std::vector<MoveDet> all_moves = all_legal_moves(color);
  while (!all_moves.empty()) {
    MoveDet mv = all_moves.back();
    all_moves.pop_back();
    auto piece_taken = b->apply(mv);
    if (is_attacked(getKing(color)) == false) {
        int val = mini(current_depth - 1, !color, best);
        if (is_attacked(getKing(!color)) == true) {
            if (is_attacked(b->getBoardConfig(mv.new_line, mv.new_col)) == false) {
                val += 2000;
            }
        }
        if (is_check_mate(!color) == true) {
            val += 200000;
        }
        if (val > best) {
          best = val;
          //   we HAVE TO make sure our bot makes the move
          if (color == b->getColorBot()) {
            best_move = mv;
          }
        }
    }
    b->undo(piece_taken, mv);
    if (best > beta) {
        break;
    }
  }
  return best;
}

 int mini(int current_depth, bool color, int alfa) {
   if (current_depth == 0) {
     return -evaluate(color);
   }
   int best = INT_MAX;
   std::vector<MoveDet> all_moves = all_legal_moves(color);
   while (!all_moves.empty()) {
     MoveDet mv = all_moves.back();
     all_moves.pop_back();
     auto piece_taken = b->apply(mv);
     if (is_attacked(getKing(color)) == false) {
         int val = maxi(current_depth - 1, !color, best);
         if (is_attacked(getKing(!color)) == true) {
             if (is_attacked(b->getBoardConfig(mv.new_line, mv.new_col)) == false) {
                 val -= 2000;
             }
         }
         if (is_check_mate(!color) == true) {
             val -= 200000;
         }
         if (val < best) {
           best = val;
           // we HAVE TO make sure our bot makes the move
           if (color == b->getColorBot()) {
             best_move = mv;
           }
         }
     }
     b->undo(piece_taken, mv);
     if (best < alfa) {
         break;
     }
   }
   return best;
 }


#endif
