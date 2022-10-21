#include "square.h"

ClassicSquare::ClassicSquare(char kind) : Square(kind) {
}

error* ClassicSquare::Draw() {
  printf("draw classic square [%c]\n", this->kind);
  return NULL;
}
