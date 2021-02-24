#ifndef BISHOP_MOVES_H
#define BISHOP_MOVES_H
#include "../board.h"

std::vector<MoveDet> get_basic_bishop(Piece p);
std::vector<MoveDet> get_attack_bishop(Piece p);

std::vector<MoveDet> get_moves_bishop(Piece p) {
    std::vector<MoveDet> mv, aux_mov;
    mv = get_basic_bishop(p);
    aux_mov = get_attack_bishop(p);
    mv.insert(mv.end(), aux_mov.begin(), aux_mov.end());
    return mv;
}

std::vector<MoveDet> get_basic_bishop(Piece p) {
  std::vector<MoveDet> mv;
  int line = p.line, col = p.col;
  PieceType type = p.type;
  Piece piece;

  // top right
  piece = b->getBoardConfig(line + 1, col + 1);

  while (piece.type!= EDGE) {
    if (piece.type == NONE) {
      MoveDet move(line, col, piece.line, piece.col, type);
      mv.push_back(move);
    } else {
      break;
    }
    piece = b->getBoardConfig(piece.line + 1, piece.col + 1);
  }

  // top left
  piece = b->getBoardConfig(line + 1, col - 1);
  while (piece.type != EDGE) {
    if (piece.type == NONE) {
      MoveDet move(line, col, piece.line, piece.col, type);
      mv.push_back(move);
    } else {
      break;
    }
    piece = b->getBoardConfig(piece.line + 1, piece.col - 1);
  }

  // bottom left
  piece = b->getBoardConfig(line - 1, col - 1);
  while (piece.type != EDGE) {
    if (piece.type == NONE) {
      MoveDet move(line, col, piece.line, piece.col, type);
      mv.push_back(move);
    } else {
      break;
    }
    piece = b->getBoardConfig(piece.line - 1, piece.col - 1);
  }

  // bottom right
  piece = b->getBoardConfig(line - 1, col + 1);
  while (piece.type != EDGE) {
    if (piece.type == NONE) {
      MoveDet move(line, col, piece.line, piece.col, type);
      mv.push_back(move);
    } else {
      break;
    }
    piece = b->getBoardConfig(piece.line - 1, piece.col + 1);
  }
  return mv;

}

std::vector<MoveDet> get_attack_bishop(Piece p) {
  std::vector<MoveDet> mv;
  int line = p.line, col = p.col;
  PieceType type = p.type;

  Piece piece;
  // top right
  piece = b->getBoardConfig(line + 1, col + 1);
  while (piece.type != EDGE) {
    if (piece.color == p.color) {
      break;
    }
    if (piece.color != p.color && piece.color != NO_COL) { // oponent
      MoveDet move(line, col, piece.line, piece.col, type);
      mv.push_back(move);
      break;
    }
    piece = b->getBoardConfig(piece.line + 1, piece.col + 1);
  }

  // bottom right
  piece = b->getBoardConfig(line + 1, col - 1);
  while (piece.type != EDGE) {
    if (piece.color == p.color) {
      break;
    }
    if (piece.color != p.color && piece.color != NO_COL) { // oponent
      MoveDet move(line, col, piece.line, piece.col, type);
      mv.push_back(move);
      break;
    }
    piece = b->getBoardConfig(piece.line + 1, piece.col - 1);

  }

  // bottom left
  piece = b->getBoardConfig(line - 1, col - 1);
  while (piece.type != EDGE) {
    if (piece.color == p.color) {
      break;
    }
    if (piece.color != p.color && piece.color != NO_COL) { // oponent
      MoveDet move(line, col, piece.line, piece.col, type);
      mv.push_back(move);
      break;
    }
    piece = b->getBoardConfig(piece.line - 1, piece.col - 1);
  }

  // top left
  piece = b->getBoardConfig(line - 1, col + 1);
  while (piece.type != EDGE) {
    if (piece.color == p.color) {
      break;
    }
    if (piece.color != p.color && piece.color != NO_COL) { // oponent
      MoveDet move(line, col, piece.line, piece.col, type);
      mv.push_back(move);
      break;
    }
    piece = b->getBoardConfig(piece.line - 1, piece.col + 1);
  }
  return mv;
}

#endif
