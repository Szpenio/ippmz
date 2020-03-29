// Author: Antoni Koszowski
// Project: "Małe zadanie zaliczeniowe"

// program simulating world, consisting of:
// - forests growing up in this world
// - trees inside forests
// - animals living on this trees
// where names of trees inside forest
// as well as names of animals on trees are unique
// enabling user to:
// ADD, DELETE, PRINT objects on some/ multiple layers of abstraction
// CHECK whether objects exist on some/ multiple layers of abstraction

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

int main() {
  char *buffer;
  size_t bufsize = 32;

  // creating the world (existance)
  allocExistance();

  buffer = malloc(bufsize * sizeof(char));
  if (buffer == NULL) {
    exit(1);
  }

  // processing the input
  while (getline(&buffer, &bufsize, stdin) != -1) {
    parseInputLine(buffer);
  }

  free(buffer);

  // destroying the world (existance)
  destroyExistance();

  return 0;
}
