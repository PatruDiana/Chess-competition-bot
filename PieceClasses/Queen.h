#ifndef QUEEN_H
#define QUEEN_H
#include <vector>
#include "piece.h"

class Queen : public Piece {
public:
    Queen () {}
    Queen (int color, int line, int col) {
        this->color = color;
        if (color == WHITE) {
            this->type = QUEEN_W;
        } else {
            this->type = QUEEN_B;
        }
        this->line = line;
        this->col = col;
        this->score = 900;
    }
};

#endif
