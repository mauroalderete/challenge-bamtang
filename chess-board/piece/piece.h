#ifndef _PIECE_H
#define _PIECE_H

#include <stdlib.h>
#include "../error/error.h"
#include "../drawers/drawers.h"

class PieceBase
{
protected:
  char id;

  PieceBase(char id);

public:
  char ID();
};

class Piece : public PieceBase
{
public:
  Piece(char id);

  virtual error *Draw() = 0;
};

#endif /* piece.h */
