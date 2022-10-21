#ifndef _PIECEFACTORY_H
#define _PIECEFACTORY_H

#include <stdlib.h>
#include "../error/error.h"
#include "piece.h"
#include "../drawers/drawers.h"
#include "../drawers/console/piece.h"
#include "../drawers/classic/piece.h"

class PieceFactory {
private:
  CHESSBOARD_STYLE style;

public:
  PieceFactory(CHESSBOARD_STYLE style);

  virtual Piece* CreatePiece(char id);
};

#endif /* piecefactory.h */
