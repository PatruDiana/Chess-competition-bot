#ifndef KING_H
#define KING_H
#include <vector>
#include "piece.h"

class King : public Piece {
public:
    King () {}
    King (int color, int line, int col) {
        this->color = color;
        if (color == WHITE) {
            this->type = KING_W;
        } else {
            this->type = KING_B;
        }
        this->line = line;
        this->col = col;
        this->score = 20000;
    }
};

#endif
