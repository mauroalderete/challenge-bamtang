#include "piecefactory.h"

PieceFactory::PieceFactory(CHESSBOARD_STYLE style)
{
  this->style = style;
}

Piece *PieceFactory::CreatePiece(char id)
{
  switch (this->style)
  {
  case console:
    return (Piece *)(new ConsolePiece(id));
    break;
  case classic:
    return (Piece *)(new ClassicPiece(id));
    break;

  default:
    return NULL;
    break;
  }
  return NULL;
}
