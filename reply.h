#ifndef REPLY_H
#define REPLY_H
#include "MiniMax.h"
#include "board.h"
void reply(){
    Board* b = Board::getBoard();
    b->setScore();
    MoveDet m = minimax(2);
    std::cout << "move " << (char)(m.old_col + 'a' - 1)
      << m.old_line <<(char)(m.new_col + 'a' - 1)
      << m.new_line << std::endl;
    b->apply(m);
    b->showBoard();
}

#endif
