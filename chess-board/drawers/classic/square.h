#ifndef _CLASSIC_SQUARE_H
#define _CLASSIC_SQUARE_H

#include <stdio.h>
#include "../../error/error.h"
#include "../../square/square.h"

class ClassicSquare : public Square
{
public:
  ClassicSquare(char kind);

  error* Draw() override;
};

#endif /* square.h */
