#include "boardfactory.h"

BoardFactory::BoardFactory(CHESSBOARD_STYLE style)
{
  this->style = style;
}

Board *BoardFactory::CreateBoard(size_t rows, size_t columns)
{
  switch (this->style)
  {
  case console:
    return (Board *)(new ConsoleBoard(rows, columns));
    break;

  case classic:
    return (Board *)(new ClassicBoard(rows, columns));
    break;

  default:
    return NULL;
    break;
  }
}