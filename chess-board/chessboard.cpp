#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <unordered_map>
#include "error/error.h"

#include "piece/piece.h"
#include "piece/piecefactory.h"

error* drawChessBoard( const char *position ) {

  PieceFactory *consolePieceFactory = new PieceFactory(console);
  Piece *consoleKing = consolePieceFactory->CreatePiece('k');
  consoleKing->Draw();

  PieceFactory *classicPieceFactory = new PieceFactory(classic);
  Piece *classicKing = classicPieceFactory->CreatePiece('k');
  classicKing->Draw();

  return NULL;
}

int main() {

  printf("main:0\n");

  const char *initPosition = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";

  printf("main:1\n");
  error *err = drawChessBoard(initPosition);
  if (err!=NULL) {
    printf("main:1.1\n");
    fatal(err);
  }

  printf("main:2\n");
  exit(EXIT_SUCCESS);
}
