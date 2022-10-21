#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <unordered_map>
#include "error/error.h"

#include "piece/piece.h"
#include "piece/piecefactory.h"
#include "square/square.h"
#include "square/squarefactory.h"

error* drawChessBoard( const char *position ) {

  PieceFactory *consolePieceFactory = new PieceFactory(console);
  Piece *consoleKing = consolePieceFactory->CreatePiece('k');
  consoleKing->Draw();

  PieceFactory *classicPieceFactory = new PieceFactory(classic);
  Piece *classicKing = classicPieceFactory->CreatePiece('K');
  classicKing->Draw();

  SquareFactory *consoleSquareFactory = new SquareFactory(console);
  Square *consoleSquareWhite1 = consoleSquareFactory->CreateSquare('w');
  consoleSquareWhite1->Put(consoleKing);
  consoleSquareWhite1->Draw();
  Square *consoleSquareBlack1 = consoleSquareFactory->CreateSquare('b');
  consoleSquareBlack1->Put(consoleKing);
  consoleSquareBlack1->Draw();

  printf("\n");

  Square *consoleSquareWhite2 = consoleSquareFactory->CreateSquare('w');
  consoleSquareWhite1->Put(classicKing);
  consoleSquareWhite1->Draw();
  Square *consoleSquareBlack2 = consoleSquareFactory->CreateSquare('b');
  consoleSquareBlack2->Put(classicKing);
  consoleSquareBlack2->Draw();

  printf("\n");
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
