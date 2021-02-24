#ifndef CHECK_CHECKMATE_H
#define CHECK_CHECKMATE_H
#include "board.h"
#include "./MovePieces/moves.h"
#include <vector>

// position (piece.line, piece.col) is attacked by one of the pieces of specified color
// ex: black king is attacked by one of the white pieces?
bool is_attacked(Piece p) {
    std::ofstream debug;
    debug.open("attack.txt");
    std::vector<MoveDet> moves = all_legal_moves(!p.color); // get all the possible replies
    debug << p.color << " " << moves.size() << " is_attacked\n";
    for (auto mv : moves) {
        debug << mv.piece << " " << mv.old_line << " " << mv.old_col
        << " " << mv.new_line << " " << mv.new_col << "\n";
        if (mv.new_line == p.line && mv.new_col == p.col) { //the new pos of a reply
            return true;                // is equal to position I search => attacked
        }
    }
    debug.close();
    return false;
}

Piece getKing(bool color) {
    if (color == BLACK) {
        for (auto p : b->pieces_black) {
            if (p.type == KING_B) {
                return p;
            }
        }
    } else if (color == WHITE) {
        for (auto p : b->pieces_white) {
            if (p.type == KING_W) {
                return p;
            }
        }
    }
    Piece none(0, 0);
    return none;
}

// generate all of the moves from white and check if they get rid of the attack
// if so, add them to the array of replies
std::vector<MoveDet> reply_to_check(bool color) {
    std::vector<MoveDet> replies, moves = all_legal_moves(color);
    for (auto mv : moves) {
        Piece p = b->apply(mv);
        if (is_attacked(getKing(color)) == false) {
            replies.push_back(mv);
        }
        b->undo(p, mv);
    }
    return replies;
}

// the player on the specified color is in mate
bool is_check_mate(bool color) {
    if (is_attacked(getKing(color)) == true) {
        std::vector<MoveDet> replies = reply_to_check(color);
        if (replies.size() == 0) {
            return true;
        }
    }
    return false;
}

#endif
