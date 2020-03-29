#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "agent.h"
#include "parser.h"


// checks whether [input_line] begins with '#'
static bool commentLine(char *input_line) {
  if (input_line[0] == '#') {
    return true;
  }

  return false;
}

// checks whether [input_line] ends with '\n'
static bool endlEnding(char *input_line) {
  int i = 0;
  bool endl_ending = false;

  for (i = strlen(input_line) - 1; i > 0 && !endl_ending; --i) {
    if (input_line[i] == '\n') {
      endl_ending = true;
    }
  }

  return endl_ending;
}

// checks if characters in [input_line] are in <33, 255> ASCII code
static bool outOfRange(char *token) {
  int i = 0;
  bool out_of_range = false;

  for (i = strlen(token) - 1; i > 0 && !out_of_range; --i) {
    if ((unsigned char)token[i] < 32) {
      out_of_range = true;
    }
  }
  return out_of_range;
}

// matches the right command and then executes it,
// otherwise prints "ERROR" to stderr
static void chooseOption(char **params, int p_number) {
  const char *command = params[0];

  // ADD must have between <1, 3> parameters
  if (strcmp(command, "ADD") == 0 && p_number > 0) {
    ADD(params, p_number);
    puts("OK");
  }
  // DEL must have between <0, 3> parameters
  else if (strcmp(command, "DEL") == 0) {
    DEL(params, p_number);
    puts("OK");
  }
  // PRINT must have between <0, 2> parameters
  else if (strcmp(command, "PRINT") == 0 && p_number < 3) {
    PRINT(params, p_number);
  }
  // check must have between <1, 3> parameters
  // and the last one cannot be single '*'
  else if (strcmp(command, "CHECK") == 0 && p_number > 0) {
    if (params[p_number][0] != '*' || strlen(params[p_number]) > 1) {
      if (CHECK(params, p_number)) {
        puts("YES");
      }
      else {
        puts("NO");
      }
    }
    else {
      fprintf(stderr, "ERROR\n");
      return;
    }
  }
  // no match
  else {
    fprintf(stderr, "ERROR\n");
    return;
  }
}

void parseInputLine(char *input_line) {
  char *token, *params[4];
  const char *delim = " \t\v\f\r\n";
  int p_count = 0;
  bool endl_ending = false;

  // input begining with '#'
  if (commentLine(input_line)) {
    return;
  }

  // checks if line is ending with '\n'
  endl_ending = endlEnding(input_line);

  // checks for string of whitespaces or NULL input, reads first parameter
  // strtok slices [input_line] into strings partitioned by signs from [delim]
  if (!(token = strtok(input_line, delim))) {
    return;
  }
  else if (!endl_ending) {
    fprintf(stderr, "ERROR\n");
    return;
  }

  params[p_count++] = token;

  // reads next parameters, controlling their number and
  // checking whether input characters are in range <33, 255>
  while ((token = strtok(0, delim))) {
    if (p_count < 4) {
      params[p_count++] = token;
      if (outOfRange(token)) {
        fprintf(stderr, "ERROR\n");
        return;
      }
    }
    // too much parameters
    else {
      fprintf(stderr, "ERROR\n");
      return;
    }
  }

  // chooses right command or prints ERROR to stderr in case of no match
    chooseOption(params, p_count - 1);
}
