#ifndef PIECE_H
#define PIECE_H
#include <vector>
enum PieceType{NONE, PAWN_W, ROOK_W, KNIGHT_W, BISHOP_W, QUEEN_W, KING_W,
    PAWN_B, ROOK_B, KNIGHT_B, BISHOP_B, QUEEN_B, KING_B, EDGE};

class MoveDet {
public:
    int new_line, new_col;
    int old_line, old_col;
    PieceType piece;
    MoveDet () {}
    MoveDet (int o_line, int o_col, int n_line, int n_col, PieceType n_piece) {
        old_line = o_line;
        old_col = o_col;
        new_line = n_line;
        new_col = n_col;
        piece = n_piece;
    }
};

class Piece {
    void init_score(PieceType p) {
        if (p == PAWN_B || p == PAWN_W) {
            this->score = 1;
        } else if (p == ROOK_B || p == ROOK_W) {
            this->score = 5;
        } else if (p == KNIGHT_B || p == KNIGHT_W) {
            this->score = 3;
        } else if (p == BISHOP_B || p == BISHOP_W) {
            this->score = 3;
        } else if (p == QUEEN_B || p == QUEEN_W) {
            this->score = 9;
        } else {
            this->score = 0;
        }
    }

public:
    PieceType type;
    int color; // 0 = white; 1 = black
    int line, col;
    int score;

    Piece () {}
    Piece (PieceType type, int line, int col) {
        this->type = type;
        if (type == 0) {
            this->color = NO_COL;
        } else if (type >= 1 && type <= 6){
            this->color = WHITE;
        } else {
            this->color = BLACK;
        }
        this->line = line;
        this->col = col;
        init_score(type);
    }
    Piece (PieceType type, int color, int line, int col) {
        this->type = type;
        this->color = color;
        this->line = line;
        this->col = col;
        init_score(type);
    }
    Piece (int line, int col) {
        this->type = NONE;
        this->color = NO_COL;
        this->line = line;
        this->col = col;
        this->score = 0;
    }

    Piece& operator=(const Piece& other) {
        this->type = other.type;
        this->color = other.color;
        this->line = other.line;
        this->col = other.col;
        this->score = other.score;
        return *this;
    }
    friend std::ostream& operator << (std::ostream &out, const Piece &p) {
    out << "(" << p.type << ", " << p.line << ", " << p.col << ") ";
    return out;
  }
};

class Edge : public Piece {
public:
    Edge (int line, int col) {
        this->type = EDGE;
        this->color = NO_COL;
        this->line = line;
        this->col = col;
        this->score = 0;
    }
};

#endif
