#include "board.h"

BoardBase::BoardBase(size_t rows, size_t columns)
{
  this->rows = rows;
  this->columns = columns;
}

size_t BoardBase::Rows()
{
  return this->rows;
}

size_t BoardBase::Columns()
{
  return this->columns;
}

size_t BoardBase::Size()
{
  return this->rows * this->columns;
}

Square *BoardBase::SquareAt(size_t i)
{
  if (i >= this->squares.size())
  {
    return NULL;
  }
  return this->squares.at(i);
}

Board::Board(size_t rows, size_t columns) : BoardBase(rows, columns)
{
}
