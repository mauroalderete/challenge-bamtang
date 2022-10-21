#include "piece.h"

ClassicPiece::ClassicPiece(char id) : Piece(id) {
}

error* ClassicPiece::Draw() {
  printf("draw classic piece %c\n", this->id);
  return NULL;
}
