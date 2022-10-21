#ifndef _CONSOLE_BOARD_H
#define _CONSOLE_BOARD_H

#include <stdio.h>
#include "../../error/error.h"
#include "../../board/board.h"
#include "square.h"

class ConsoleBoard : public Board
{
private:
  void buildBoard() override;

public:
  ConsoleBoard(size_t rows, size_t columns);

  error* Draw() override;
};

#endif /* console/board.h */
