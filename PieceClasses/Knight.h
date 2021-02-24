#ifndef KNIGHT_H
#define KNIGHT_H
#include <vector>
#include "piece.h"

class Knight : public Piece {
public:
    Knight () {}
    Knight (int color, int line, int col) {
        this->color = color;
        if (color == WHITE) {
            this->type = KNIGHT_W;
        } else {
            this->type = KNIGHT_B;
        }
        this->line = line;
        this->col = col;
        this->score = 320;
    }
};

#endif
