#include "board.h"

ClassicBoard::ClassicBoard(size_t rows, size_t columns) : Board(rows, columns)
{
  this->buildBoard();
}

void ClassicBoard::buildBoard()
{
  this->squares.clear();
  this->squares.resize(rows * columns, NULL);

  for (int s = 0; s < this->squares.size(); s++)
  {
    if (s % 2 == 0)
    {
      this->squares.at(s) = (Square *)(new ClassicSquare('w'));
    }
    else
    {
      this->squares.at(s) = (Square *)(new ClassicSquare('b'));
    }
  }
}

error *ClassicBoard::Draw()
{
  printf("ClassicBoard:1\n");
  for (int r = 0; r < this->rows; r++)
  {
    for (int c = 0; c < this->columns; c++)
    {
      printf("\t r=%i c=%i => ", r, c);
      Square *s = this->squares[r * this->rows + c];

      if (s == NULL)
      {
        printf("AAAAAAAAA\n");
      }
      else
      {
        printf("bbb\n");
      }

      s->Draw();
    }
    printf("\n");
  }
  printf("ClassicBoard:2\n");
  return NULL;
}