#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "err.h"

error* drawChessBoard( const char *position ) {
  return NULL;
}

int main() {

  printf("Jaque mate!\n");

  const char *initPosition = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";

  error *err = drawChessBoard(initPosition);
  if (err!=NULL) {
    fatal(err);
  }  

  exit(EXIT_SUCCESS);
}
