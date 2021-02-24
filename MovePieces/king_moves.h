#ifndef KING_MOVES_H
#define KING_MOVES_H
#include "../board.h"
std::vector<MoveDet> get_basic_king(Piece p);
std::vector<MoveDet> get_attack_king(Piece p);

std::vector<MoveDet> get_moves_king(Piece p) {
    std::vector<MoveDet> mv, aux_mov;
    mv = get_basic_king(p);
    aux_mov = get_attack_king(p);
    mv.insert(mv.end(), aux_mov.begin(), aux_mov.end());
    return mv;
}

bool is_king_in_neighbours(Piece p, bool color) {
    std::vector<Piece> neighbours;
    int line = p.line, col = p.col;
    int coord_x[9] = { 1, 1, 1, 0, -1, -1, -1,  0},
        coord_y[9] = {-1, 0, 1, 1,  1,  0, -1, -1};
    for (int i = 0; i < 8; i++) {
        Piece n = b->getBoardConfig(line + coord_x[i], col + coord_y[i]);
        if (color == WHITE) {
            if (n.type == KING_B) {
                return true;
            }
        } else if(color == BLACK) {
            if (n.type == KING_W) {
                return true;
            }
        }
    }
    return false;
}

std::vector<MoveDet> get_basic_king(Piece p) {
    std::vector<MoveDet> mv;
    int line = p.line, col = p.col;
    PieceType type = p.type;
    Piece up = b->getBoardConfig(line + 1, col);
    Piece up_left = b->getBoardConfig(line + 1, col - 1);
    Piece up_right = b->getBoardConfig(line + 1, col + 1);
    Piece left = b->getBoardConfig(line, col - 1);
    Piece right = b->getBoardConfig(line, col + 1);
    Piece down = b->getBoardConfig(line - 1, col);
    Piece down_left = b->getBoardConfig(line - 1, col - 1);
    Piece down_right = b->getBoardConfig(line - 1, col + 1);

    if (up.type == NONE && is_king_in_neighbours(up, p.color) == false) {
        MoveDet move(line, col, up.line, up.col, type);
        mv.push_back(move);
    }
    if (up_left.type == NONE && is_king_in_neighbours(up_left, p.color) == false) {
        MoveDet move(line, col, up_left.line, up_left.col, type);
        mv.push_back(move);
    }
    if (up_right.type == NONE && is_king_in_neighbours(up_right, p.color) == false) {
        MoveDet move(line, col, up_right.line, up_right.col, type);
        mv.push_back(move);
    }
    if (down.type == NONE && is_king_in_neighbours(down, p.color) == false) {
        MoveDet move(line, col, down.line, down.col, type);
        mv.push_back(move);
    }
    if (down_left.type == NONE && is_king_in_neighbours(down_left, p.color) == false) {
        MoveDet move(line, col, down_left.line, down_left.col, type);
        mv.push_back(move);
    }
    if (down_right.type == NONE && is_king_in_neighbours(down_right, p.color) == false) {
        MoveDet move(line, col, down_right.line, down_right.col, type);
        mv.push_back(move);
    }
    if (left.type == NONE && is_king_in_neighbours(left, p.color) == false) {
        MoveDet move(line, col, left.line, left.col, type);
        mv.push_back(move);
    }
    if (right.type == NONE && is_king_in_neighbours(right, p.color) == false) {
        MoveDet move(line, col, right.line, right.col, type);
        mv.push_back(move);
    }
    return mv;
}

std::vector<MoveDet> get_attack_king(Piece p) {
    std::vector<MoveDet> mv;
    int line = p.line, col = p.col;
    PieceType type = p.type;
    Piece up = b->getBoardConfig(line + 1, col);
    Piece up_left = b->getBoardConfig(line + 1, col - 1);
    Piece up_right = b->getBoardConfig(line + 1, col + 1);
    Piece left = b->getBoardConfig(line, col - 1);
    Piece right = b->getBoardConfig(line, col + 1);
    Piece down = b->getBoardConfig(line - 1, col);
    Piece down_left = b->getBoardConfig(line - 1, col - 1);
    Piece down_right = b->getBoardConfig(line - 1, col + 1);

    if (up.color != p.color && up.color != NO_COL && is_king_in_neighbours(up, p.color) == false) {
        MoveDet move(line, col, up.line, up.col, type);
        mv.push_back(move);
    }
    if (up_left.color != p.color && up_left.color != NO_COL && is_king_in_neighbours(up_left, p.color) == false) {
        MoveDet move(line, col, up_left.line, up_left.col, type);
        mv.push_back(move);
    }
    if (up_right.color != p.color && up_right.color != NO_COL && is_king_in_neighbours(up_right, p.color) == false) {
        MoveDet move(line, col, up_right.line, up_right.col, type);
        mv.push_back(move);
    }
    if (down.color != p.color && down.color != NO_COL && is_king_in_neighbours(down, p.color) == false) {
        MoveDet move(line, col, down.line, down.col, type);
        mv.push_back(move);
    }
    if (down_left.color != p.color && down_left.color != NO_COL && is_king_in_neighbours(down_left, p.color) == false) {
        MoveDet move(line, col, down_left.line, down_left.col, type);
        mv.push_back(move);
    }
    if (down_right.color != p.color && down_right.color != NO_COL && is_king_in_neighbours(down_right, p.color) == false) {
        MoveDet move(line, col, down_right.line, down_right.col, type);
        mv.push_back(move);
    }
    if (left.color != p.color && left.color != NO_COL && is_king_in_neighbours(left, p.color) == false) {
        MoveDet move(line, col, left.line, left.col, type);
        mv.push_back(move);
    }
    if (right.color != p.color && right.color != NO_COL && is_king_in_neighbours(right, p.color) == false) {
        MoveDet move(line, col, right.line, right.col, type);
        mv.push_back(move);
    }
    return mv;
}

#endif
