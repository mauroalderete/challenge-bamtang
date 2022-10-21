#include "piece.h"

PieceBase::PieceBase(char id)
{
  this->id = id;
}

char PieceBase::ID()
{
  return this->id;
}

Piece::Piece(char id) : PieceBase(id) {}
