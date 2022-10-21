#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <unordered_map>
#include "error/error.h"

#include "board/board.h"
#include "drawers/console/board.h"
#include "drawers/classic/board.h"

error* drawChessBoard( const char *position ) {

  
  Board *consoleBoard = new ConsoleBoard(8,8);
  consoleBoard->Draw();
  
  printf("\n");

  Board *classicBoard = new ClassicBoard(8,8);
  classicBoard->Draw();
  
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
