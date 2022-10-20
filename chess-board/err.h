/**
 * err.h implements a serie of struct and functions to manipulate expected errors.
*/

#ifndef _ERR_H
#define _ERR_H

/**
 * Implements a simple struct to manipulate errors.
*/
struct error {
  char *message;  // Stores a description of one error.
};

/**
 * Returns a new error with the description string as a value that satisfies error.
*/
error * errorf(const char *message);

/**
 * Prints the error description and stop the current process with a failure exit code.
 * Fatal is equivalent to Print() followed by a call to Exit(EXIT_FAILURE)
*/
void fatal(error *err);

#endif /* err.h */
