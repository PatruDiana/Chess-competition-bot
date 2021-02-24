#ifndef BISHOP_H
#define BISHOP_H
#include <vector>
#include "piece.h"

class Bishop : public Piece {
public:
    Bishop () {}
    Bishop (int color, int line, int col) {
        this->color = color;
        if (color == WHITE) {
            this->type = BISHOP_W;
        } else {
            this->type = BISHOP_B;
        }
        this->line = line;
        this->col = col;
        this->score = 330;
    }
};

#endif
