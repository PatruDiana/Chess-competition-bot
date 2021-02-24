#ifndef PAWN_H
#define PAWN_H
#include <vector>
#include "piece.h"

class Pawn : public Piece {
public:
    Pawn () {}
    Pawn (int color, int line, int col) {
        this->color = color;
        if (color == WHITE) {
            this->type = PAWN_W;
        } else {
            this->type = PAWN_B;
        }
        this->line = line;
        this->col = col;
        this->score = 100;
    }
};

#endif
