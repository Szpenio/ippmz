#ifndef AGENT_H
#define AGENT_H

// creates the world (existance),
// allocates memory and initializes component parts of the existance
void allocExistance();

// destroys the world (existance),
// destroys all the component parts and deallocates all occupied memory
void destroyExistance();

// for each operation function communicating with data structure is provided
// executing operations for [parameters][their_number], in general:
// - no parameter is related to the whole existance
// - first (if read) parameter is related to forest,
// - second (if read) is related to tree,
// - third (if read) is related to animal

// adds objects from [params] on each given layer of abstraction,
// if object was already added, command on this layer of abstraction is ignored,
// properly executed prints "OK" to stdout
void ADD(char **params, int p_number);

// deletes objects from [params] on each given layer of abstraction,
// provided that previous layer exists, otherwise command is ignored;
// DEL without parameters removes all objects (apart from existance),
// properly executed prints "OK" to stdout
void DEL(char **params, int p_number);

// prints all objects from last layer from [params] if such exists,
// otherwise ingored
void PRINT(char **params, int p_number);

// checks if objects from consecutive layers from [params] exists,
// if so prints "YES", otherwise "NO";
// '*' is a special sign matching any name, it cannot be the last parameter
bool CHECK(char **params, int p_number);

#endif
