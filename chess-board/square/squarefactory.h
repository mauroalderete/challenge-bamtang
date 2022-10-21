#ifndef _SQUAREFACTORY_H
#define _SQUAREFACTORY_H

#include <stdlib.h>
#include "../error/error.h"
#include "square.h"
#include "../drawers/drawers.h"
#include "../drawers/console/square.h"
#include "../drawers/classic/square.h"

class SquareFactory {
private:
  CHESSBOARD_STYLE style;

public:
  SquareFactory(CHESSBOARD_STYLE style);

  virtual Square* CreateSquare(char kind);
};

#endif /* squarefactory.h */
