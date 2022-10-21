#include "square.h"
#include "../piece/piece.h"
#include "../drawers/console/piece.h"

SquareBase::SquareBase(char kind)
{
  this->kind = kind;
  this->piece = NULL;
}

Piece *SquareBase::Put(Piece *piece)
{
  Piece *tmp = this->Take();
  this->piece = piece;
  return tmp;
}

Piece *SquareBase::Take()
{
  Piece *tmp = this->piece;
  this->piece = NULL;
  return tmp;
}

char SquareBase::Kind()
{
  return this->kind;
}

Square::Square(char kind) : SquareBase(kind)
{
}
