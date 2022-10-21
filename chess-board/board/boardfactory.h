#ifndef _BOARDFACTORY_H
#define _BOARDFACTORY_H

#include <stddef.h>
#include "../error/error.h"
#include "board.h"
#include "../drawers/console/board.h"
#include "../drawers/classic/board.h"

class BoardFactory
{
private:
  CHESSBOARD_STYLE style;
public:
  BoardFactory(CHESSBOARD_STYLE style);

  Board *CreateBoard(size_t rows, size_t columns);
};

#endif
