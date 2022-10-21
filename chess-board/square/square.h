#ifndef _SQUARE_H
#define _SQUARE_H

#include <stdlib.h>
#include "../error/error.h"
#include "../piece/piece.h"

class SquareBase
{
protected:
  char kind;
  Piece *piece;

  SquareBase(char kind);

public:
  Piece *Put(Piece *piece);

  Piece *Take();

  char Kind();
};

class Square : public SquareBase {
public:
  Square(char kind);

  virtual error* Draw() = 0;
};

#endif /* square.h */
