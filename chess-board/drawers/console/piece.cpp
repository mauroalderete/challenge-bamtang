#include "piece.h"

ConsolePiece::ConsolePiece(char id) : Piece(id) {
}

error* ConsolePiece::Draw() {
  printf("draw cnosole piece %c\n", this->id);
  return NULL;
}
