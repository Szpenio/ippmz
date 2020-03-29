#ifndef PARSER_H
#define PARSER_H

// creates the world (existance),
// allocates memory and initializes component parts of the existance
void allocExistance();

// destroys the world (existance),
// destroys all the component parts and deallocates all occupied memory
void destroyExistance();

// processes the input,
// checks for its correctness in accordance with requirements:
// - only signs from extended ASCII i.e. with codes <33, 255>
// - each proper command should appear in separate line ending up with '\n'
// - whitespaces (i.e. ' ', '\t', '\v', '\f', '\r') are ignored
// - lines begining with '#' are ignored
// in case those requirements are met input is matched with one of the commands:
// - ADD, DEL, PRINT, CHECK,
// if matched and number of parameters is correct executed;
// otherwise "ERROR" is printed to stderr
void parseInputLine(char *input_line);

#endif
