#ifndef _CLASSIC_BOARD_H
#define _CLASSIC_BOARD_H

#include <stdio.h>
#include "../../error/error.h"
#include "../../board/board.h"
#include "square.h"

class ClassicBoard : public Board
{
protected:
  void buildBoard() override;

public:
  ClassicBoard(size_t rows, size_t columns);

  error* Draw() override;
};

#endif /* classic/board.h */
