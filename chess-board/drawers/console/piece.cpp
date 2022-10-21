#include "piece.h"

ConsolePiece::ConsolePiece(char id) : Piece(id) {
}

error* ConsolePiece::Draw() {
  printf("draw console piece %c\n", this->id);
  return NULL;
}
