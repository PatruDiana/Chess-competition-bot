#ifndef ROOK_H
#define ROOK_H
#include <vector>
#include "piece.h"

class Rook : public Piece {
public:
    Rook () {}
    Rook (int color, int line, int col) {
        this->color = color;
        if (color == WHITE) {
            this->type = ROOK_W;
        } else {
            this->type = ROOK_B;
        }
        this->line = line;
        this->col = col;
        this->score = 500;
    }
};

#endif
