#include "square.h"

ConsoleSquare::ConsoleSquare(char kind) : Square(kind) {
}

error* ConsoleSquare::Draw() {
  
  char piece = ' ';
  if (this->piece != NULL)
  {
    piece = this->piece->ID();
  }

  if (this->kind == 'w') {
    printf(" [%c]", piece);
  } else {
    printf(" {%c}", piece);
  }

  return NULL;
}
