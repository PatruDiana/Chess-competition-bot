#ifndef BOARD_H
#define BOARD_H
#define LEN 9
#define WHITE 0
#define BLACK 1
#define NO_COL -1
#include "./PieceClasses/piece.h"
#include "./PieceClasses/Pawn.h"
#include "./PieceClasses/Rook.h"
#include "./PieceClasses/Bishop.h"
#include "./PieceClasses/Knight.h"
#include "./PieceClasses/Queen.h"
#include "./PieceClasses/King.h"
#include "./MovePieces/strategy_moves.h"
#include <algorithm>
#include <vector>

int strategy_points(int line, int col, bool color);
class Board {
    static Board *instance;
    bool bot_color;
    Board() {   //constructor inits the board
        score_opponent = 0;
        score_bot = 0;
        for (int i = 1; i < LEN; ++i) {
            for (int j = 1; j < LEN; ++j) {
                init_white(i, j);
                init_black(i, j);
                if ((i + j) % 2 == 0) {
                    boardConfig[i][j].color = BLACK;
                } else {
                    boardConfig[i][j].color = WHITE;
                }
            }
        }
        bot_color = BLACK;
        std::reverse(pieces_white.begin(), pieces_white.end());
    }
    void init_white(int i, int j) {
        if (i == 2) {
            // Piece p(PAWN_W, WHITE, i, j);
            Pawn p(WHITE, i, j);
            boardConfig[i][j] = p;
            pieces_white.push_back(p);
        } else if (i == 1) {
            if (j == 1 || j == 8) {
                // Piece p(ROOK_W, WHITE, i, j);
                Rook p(WHITE, i, j);
                boardConfig[i][j] = p;
                pieces_white.push_back(p);
            } else if (j == 2 || j == 7) {
                // Piece p(KNIGHT_W, WHITE, i, j);
                Knight p(WHITE, i, j);
                boardConfig[i][j] = p;
                pieces_white.push_back(p);
            } else if (j == 3 || j == 6) {
                // Piece p(BISHOP_W, WHITE, i, j);
                Bishop p(WHITE, i, j);
                boardConfig[i][j] = p;
                pieces_white.push_back(p);
            } else if (j == 4) {
                // Piece p(QUEEN_W, WHITE, i, j);
                Queen p(WHITE, i, j);
                boardConfig[i][j] = p;
                pieces_white.push_back(p);
            } else if (j == 5) {
                // Piece p(KING_W, WHITE, i, j);
                King p(WHITE, i, j);
                boardConfig[i][j] = p;
                pieces_white.push_back(p);
            }
        }
    }
    void init_black(int i, int j) {
        if (i == 7) {
            // Piece p(PAWN_B, BLACK, i, j);
            Pawn p(BLACK, i, j);
            boardConfig[i][j] = p;
            pieces_black.push_back(p);
        } else if (i == 8) {
            if (j == 1 || j == 8) {
                // Piece p(ROOK_B, BLACK, i, j);
                Rook p(BLACK, i, j);
                boardConfig[i][j] = p;
                pieces_black.push_back(p);
            } else if (j == 2 || j == 7) {
                // Piece p(KNIGHT_B, BLACK, i, j);
                Knight p(BLACK, i, j);
                boardConfig[i][j] = p;
                pieces_black.push_back(p);
            } else if (j == 3 || j == 6) {
                // Piece p(BISHOP_B, BLACK, i, j);
                Bishop p(BLACK, i, j);
                boardConfig[i][j] = p;
                pieces_black.push_back(p);
            } else if (j == 4) {
                // Piece p(QUEEN_B, BLACK, i, j);
                Queen p(BLACK, i, j);
                boardConfig[i][j] = p;
                pieces_black.push_back(p);
            } else if (j == 5) {
                // Piece p(KING_B, BLACK, i, j);
                King p(BLACK, i, j);
                boardConfig[i][j] = p;
                pieces_black.push_back(p);
            }
        }
    }
    void init_empty() {
        for (int i = 3; i < 7; i++) {
            for (int j = 1; j < LEN; j++) {
                Piece p(i, j);
                boardConfig[i][j] = p;
            }
        }
    }
public:
    int score_opponent;
    int score_bot;
    std::vector<Piece> pieces_white;
    std::vector<Piece> pieces_black;
    Piece boardConfig[LEN][LEN];
    static Board* getBoard() { // returns the instance
        if (!instance) {
            instance =  new Board();
        }
        return instance;
    }
    void reset_board() { // called for new command
      pieces_black.clear();
      pieces_white.clear();
        for (int i = 1; i < LEN; ++i) {
            for (int j = 1; j < LEN; ++j) {
                init_white(i, j);
                init_black(i, j);
            }
        }
        init_empty();
        bot_color = BLACK;
        std::reverse(pieces_white.begin(), pieces_white.end());
    }

    void flipBotWhite() {
      bot_color = WHITE;
      std::swap(score_bot, score_opponent);
    }
    void flipBotBlack() {
      bot_color = BLACK;
      std::swap(score_bot, score_opponent);
    }
    bool getColorBot () {
      return bot_color;
    }
    void setScore() {
      score_opponent = 0;
      score_bot = 0;
      for (int i = 1; i < LEN; i++) {
        for (int j = 1; j < LEN; j++) {
            if (getBoardConfig(i, j).color == getColorBot()) {
              score_bot += getBoardConfig(i, j).score;
              score_bot += strategy_points(i, j, getColorBot());
            } else {
              score_opponent += getBoardConfig(i, j).score;
              score_opponent += strategy_points(i, j, !getColorBot());
            }
        }
      }
    }
    PieceType getPiece(int x, int y) {
        if (x >= LEN || y >= LEN || x <= 0 || y <= 0) {
            return NONE;
        }
        return this->boardConfig[x][y].type;
    }

    Piece getBoardConfig(int x, int y) {
        if (x > 0 && x < LEN && y > 0 && y < LEN)
            return this->boardConfig[x][y];
        return Edge(x, y);
    }

    void setAllBoard(Piece newBoard[LEN][LEN]) {
      for (int i = 1; i < LEN; i++) {
        for (int j = 1; j < LEN; j++) {
          boardConfig[i][j] = newBoard[i][j];
        }
      }
    }

    // set the config
    void setBoardConfig(int old_x, int old_y,
                        int new_x, int new_y, PieceType p) {
        Piece nn(old_x, old_y);
        this->boardConfig[old_x][old_y] = nn; // set old pos to NONE
        if (p == PAWN_B) {
           if (new_x == 1) {
               Queen qpb(BLACK, new_x, new_y);
               this->boardConfig[new_x][new_y] = qpb; // board
           } else {
               Pawn pb(BLACK, new_x, new_y);
               this->boardConfig[new_x][new_y] = pb;
           }
        } else if (p == ROOK_B) {
           Rook rb(BLACK, new_x, new_y);
           this->boardConfig[new_x][new_y] = rb;
        } else if (p == KNIGHT_B) {
           Knight kb(BLACK, new_x, new_y);
           this->boardConfig[new_x][new_y] = kb;
        } else if (p == BISHOP_B) {
           Bishop bb(BLACK, new_x, new_y);
           this->boardConfig[new_x][new_y] = bb;
        } else if (p == QUEEN_B) {
           Queen qb(BLACK, new_x, new_y);
           this->boardConfig[new_x][new_y] = qb;
        } else if (p == KING_B) {
           King knb(BLACK, new_x, new_y);
           this->boardConfig[new_x][new_y] = knb;
        } else if (p == PAWN_W) {
            if (new_x == 8) {
                Queen qpw(WHITE, new_x, new_y);
                this->boardConfig[new_x][new_y] = qpw;
            } else {
               Pawn pw(WHITE, new_x, new_y);
               this->boardConfig[new_x][new_y] = pw;
           }
        } else if (p == ROOK_W) {
           Rook rw(WHITE, new_x, new_y);
           this->boardConfig[new_x][new_y] = rw;
        } else if (p == KNIGHT_W) {
           Knight kw(WHITE, new_x, new_y);
           this->boardConfig[new_x][new_y] = kw;
        } else if (p == BISHOP_W) {
           Bishop bw(WHITE, new_x, new_y);
           this->boardConfig[new_x][new_y] = bw;
        } else if (p == QUEEN_W) {
           Queen qw(WHITE, new_x, new_y);
           this->boardConfig[new_x][new_y] = qw;
        } else if (p == KING_W) {
           King knw(WHITE, new_x, new_y);
           this->boardConfig[new_x][new_y] = knw;
        }
    }

    void update_pawn_promotion(Piece p, int new_line, int new_col) {
        if (p.type == PAWN_W && new_line == 8) {
            for (unsigned int i = 0; i < pieces_white.size(); i++) {
                if (pieces_white[i].type == p.type && pieces_white[i].line == new_line
                    && pieces_white[i].col == new_col) {
                        Queen qw(WHITE, new_line, new_col);
                        pieces_white[i] = qw;
                        break;
                    }
            }
        } else if (p.type == PAWN_B && new_line == 1) {
            for (unsigned int i = 0; i < pieces_black.size(); i++) {
                if (pieces_black[i].type == p.type && pieces_black[i].line == new_line
                    && pieces_black[i].col == new_col) {
                        Queen qb(BLACK, new_line, new_col);
                        pieces_black[i] = qb;
                        break;
                    }
            }
        }
    }
    void update_no_attack(MoveDet mv) {
        for (unsigned int i = 0; i < pieces_black.size(); i++) {
            if (pieces_black[i].type == mv.piece && pieces_black[i].line == mv.old_line
                && pieces_black[i].col == mv.old_col) {
                    pieces_black[i].line = mv.new_line;
                    pieces_black[i].col = mv.new_col;
                    break;
                }
        }
        for (unsigned int i = 0; i < pieces_white.size(); i++) {
            if (pieces_white[i].type == mv.piece && pieces_white[i].line == mv.old_line
                && pieces_white[i].col == mv.old_col) {
                    pieces_white[i].line = mv.new_line;
                    pieces_white[i].col = mv.new_col;
                    break;
                }
        }
    }

    void update_attack(Piece p) {
        if (p.color == BLACK) {
            for (unsigned int i = 0; i < pieces_black.size(); i++) {
                if (pieces_black[i].type == p.type && pieces_black[i].line == p.line
                    && pieces_black[i].col == p.col) {
                        pieces_black[i].type = NONE;
                        break;
                }
            }
        } else if (p.color == WHITE) {
            for (unsigned int i = 0; i < pieces_white.size(); i++) {
                if (pieces_white[i].type == p.type && pieces_white[i].line == p.line
                    && pieces_white[i].col == p.col) {
                        pieces_white[i].type = NONE;
                        break;
                }
            }
        }
    }

    void place_back_pieces(Piece p, MoveDet mv) {
        if (p.color == WHITE) {
            for (unsigned int i = 0; i < pieces_white.size(); i++) {
                if (pieces_white[i].type == NONE && pieces_white[i].line == p.line
                    && pieces_white[i].col == p.col) {
                        pieces_white[i].type = p.type;
                        break;
                    }
            }
            for (unsigned int i = 0; i < pieces_black.size(); i++) {
                if (pieces_black[i].type == mv.piece && pieces_black[i].line == mv.new_line
                    && pieces_black[i].col == mv.new_col) {
                        pieces_black[i].line = mv.old_line;
                        pieces_black[i].col = mv.old_col;
                        break;
                    }
            }
        } else if (p.color == BLACK) {
            for (unsigned int i = 0; i < pieces_black.size(); i++) {
                if (pieces_black[i].type == NONE && pieces_black[i].line == p.line
                    && pieces_black[i].col == p.col) {
                        pieces_black[i].type = p.type;
                        break;
                    }
            }
            for (unsigned int i = 0; i < pieces_white.size(); i++) {
                if (pieces_white[i].type == mv.piece && pieces_white[i].line == mv.new_line
                    && pieces_white[i].col == mv.new_col) {
                        pieces_white[i].line = mv.old_line;
                        pieces_white[i].col = mv.old_col;
                        break;
                    }
            }
        }
    }


    Piece apply(MoveDet mv) {
        Piece p = getBoardConfig(mv.new_line, mv.new_col);
        if (p.type == NONE) { // no attack => basic move
            setBoardConfig(mv.old_line, mv.old_col, mv.new_line, mv.new_col, mv.piece);
            update_no_attack(mv);
        } else if (p.type != NONE && p.type != EDGE) { // attack
            setBoardConfig(mv.old_line, mv.old_col, mv.new_line, mv.new_col, mv.piece);
            update_attack(p);
            update_no_attack(mv);
        }
        showBoard();
        return p;
    }

    void undo(Piece p, MoveDet mv) {
        if (p.type == NONE) { // no attack => basic move
            setBoardConfig(mv.new_line, mv.new_col, mv.old_line, mv.old_col, mv.piece);
            MoveDet back(mv.new_line, mv.new_col, mv.old_line, mv.old_col, mv.piece);
            update_no_attack(back);
        } else if (p.type != NONE && p.type != EDGE) {
            setBoardConfig(mv.new_line, mv.new_col, mv.old_line, mv.old_col, mv.piece);
            boardConfig[mv.new_line][mv.new_col] = p;
            place_back_pieces(p, mv);
        }
        showBoard();
    }

    void showBoardWhenBotIsBlack(std::ofstream &debug) {
        for (int i = LEN - 1; i > 0; i--) {
            for (int j = 1; j < LEN; j++) {
                debug<< getBoardConfig(i, j).type << "\t";
            }
            debug << "\n";
        }
    }
    void showBoardWhenBotIsWhite(std::ofstream &debug) {
        for (int i = 1; i < LEN; i++) {
            for (int j = LEN - 1; j > 0; j--) {
                debug<< getBoardConfig(i, j).type << "\t";
            }
            debug << "\n";
        }
    }
    // prints the board depending on bot color
    void showBoard() {
      std::ofstream debug;
      debug.open("out_debug.txt");
      // if (getColorBot() == BLACK) {
        showBoardWhenBotIsBlack(debug);
      // } else {
      //   showBoardWhenBotIsWhite(debug);
      // }
      debug << "Black:\n";
      for (long unsigned int i  = 0; i < pieces_black.size(); i++) {
        debug << pieces_black[i] << "\t";
        if (i == 7) debug << "\n";
      }
      debug << "\nWhite:\n";
      for (long unsigned int i  = 0; i < pieces_white.size(); i++) {
        debug << pieces_white[i] << "\t";
        if (i == 7) debug << "\n";
      }
      debug << "\n";
      debug.close();
    }
};

Board *Board::instance = NULL;
Board* b = Board::getBoard();
int strategy_points(int line, int col, bool color) {
    Piece piece = b->getBoardConfig(line, col);
    if (piece.type == PAWN_B) {
      return pawn_black_strategy[line][col];
    } else if (piece.type == ROOK_B) {
      return rook_black_strategy[line][col];
    } else if (piece.type == BISHOP_B) {
      return bishop_black_stategy[line][col];
    } else if (piece.type == QUEEN_B) {
      return queen_black_strategy[line][col];
    } else if (piece.type == KNIGHT_B) {
      return knight_black_strategy[line][col];
    } else if (piece.type == KING_B) {
      return king_black_middle_game_strategy[line][col];
    } else if (piece.type == PAWN_W) {
      return pawn_white_strategy[line][col];
    } else if (piece.type == ROOK_W) {
      return rook_white_strategy[line][col];
    } else if (piece.type == BISHOP_W) {
      return bishop_white_stategy[line][col];
    } else if (piece.type ==  QUEEN_W) {
      return queen_white_strategy[line][col];
    } else if (piece.type == KING_W) {
      return king_white_middle_game_strategy[line][col];
    } else if (piece.type == KNIGHT_W) {
      return knight_white_strategy[line][col];
    }
    return 0;
}
#endif
