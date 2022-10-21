#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <unordered_map>
#include "error/error.h"

error* drawChessBoard( const char *position ) {
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
