#ifndef _BOARD_H
#define _BOARD_H

#include <vector>
#include "../error/error.h"
#include "../square/square.h"

class BoardBase
{
protected:
  std::vector<Square *> squares;
  size_t rows;
  size_t columns;

  BoardBase(size_t rows, size_t columns);

public:
  size_t Rows();

  size_t Columns();

  size_t Size();

  Square *SquareAt(size_t i);
};

class Board : public BoardBase
{
protected:
  virtual void buildBoard() = 0;

public:
  Board(size_t rows, size_t columns);

  virtual error *Draw() = 0;
};

#endif /* board.h */
