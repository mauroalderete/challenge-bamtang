#include "squarefactory.h"

SquareFactory::SquareFactory(CHESSBOARD_STYLE style)
{
  this->style = style;
}

Square *SquareFactory::CreateSquare(char kind)
{
  switch (this->style)
  {
  case console:
    return (Square *)(new ConsoleSquare(kind));
    break;
  case classic:
    return (Square *)(new ClassicSquare(kind));
    break;

  default:
    return NULL;
    break;
  }
  return NULL;
}
