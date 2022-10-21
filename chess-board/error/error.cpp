#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "error.h"

error * errorf(const char *message) {
  error *e = new error;
  strcpy(e->message, message);

  return e;
}

void fatal(error *err) {
  if (err != NULL) {
    printf("ERROR: %s", err->message);
    exit(EXIT_FAILURE);
  }
}