#include "piece.h"

PieceBase::PieceBase(char id)
{
  this->id = id;
}

Piece::Piece(char id) : PieceBase(id) {}
