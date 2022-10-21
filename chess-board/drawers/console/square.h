#ifndef _CONSOLE_SQUARE_H
#define _CONSOLE_SQUARE_H

#include <stdio.h>
#include "../../error/error.h"
#include "../../square/square.h"

class ConsoleSquare : public Square
{
public:
  ConsoleSquare(char kind);

  error* Draw() override;
};

#endif /* square.h */
