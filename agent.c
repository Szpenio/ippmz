#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "agent.h"
#include "bst.h"

// global structure storing the existance
static Tree existance = NULL;

// executes operation DEL with no parameters
static void DELWithoutParams(Tree next_layer) {
  if (next_layer->inTree != NULL) {
    removeAll(next_layer->inTree);
    next_layer->inTree = NULL;
  }
}

// creates the world (existance)
void allocExistance() {
  existance = malloc(sizeof(struct Node));
  if (existance == NULL) {
    exit(1);
  }

  existance->name = strdup("world");
  if (existance->name == NULL) {
    exit(1);
  }
  existance->inTree = NULL;
  existance->left = existance-> right = NULL;
}

// destroys the world (existance)
void destroyExistance() {
  DELWithoutParams(existance);
  removeAll(existance);
}

// adds objects to the existance from [params]
void ADD(char **params, int p_number) {
  int i;
  bool executed = false;
  Tree cur_layer, next_layer = existance;

  for (i = 1; i <= p_number; ++i) {
    cur_layer = next_layer;
    // no addition before
    if (!executed) {
      // checking whether object [params[i]] is already added
      next_layer = getPtr(cur_layer->inTree, params[i]);
      if (next_layer == NULL) {
        next_layer = insert(&cur_layer->inTree, params[i]);
        executed = true;
      }
    }
    // addition before
    else {
      next_layer = insert(&cur_layer->inTree, params[i]);
    }
  }
}

// deletes objects from [params] from existance
void DEL(char **params, int p_number) {
  if (p_number == 0) {
    DELWithoutParams(existance);
    return;
  }

  int i;
  Tree cur_layer, next_layer;
  cur_layer = next_layer = existance;

  for (i = 1; i <= p_number; ++i) {
    cur_layer = next_layer;
    // checking whether object [params[i]] exists
    next_layer = getPtr(cur_layer->inTree, params[i]);
    if (next_layer == NULL) {
      return;
    }
  }

  // removing inner layers of the object as well as the object from its layer
  removeAll(next_layer->inTree);
  next_layer->inTree = NULL;
  removeVal(&cur_layer->inTree, next_layer->name);
}

// prints all objects from last layer from [params]
void PRINT(char **params, int p_number){
  int i;
  Tree cur_layer, next_layer = existance;

  for(i = 1; i <= p_number; ++i) {
    cur_layer = next_layer;
    // checking whether object [params[i]] exists
    next_layer = getPtr(cur_layer->inTree, params[i]);
    if (next_layer == NULL) {
      return;
    }
  }

  printAll(next_layer->inTree);
}

// checks if objects from consecutive layers from [params] exists
bool CHECK(char **params, int p_number) {
  int i;
  char *next_param, *last_param;
  bool executed = true;
  Tree cur_layer, next_layer = existance;

  for (i = 1; i <= p_number && executed; ++i) {
    cur_layer = next_layer;
    // checks if the object should be looked for in next layer of abstraction
    if (strcmp(params[i], "*") == 0) {
      next_param = params[++i];
      if (strcmp(next_param, "*") == 0) {
        // it is essential to look for the object in third layer of abstraction
        last_param = params[++i];
        executed = traverse(cur_layer->inTree, next_param, last_param, true);
      }
      else {
        // checks whether we still have to take two last parameters
        // into the consideration
        if (p_number - i == 1) {
          last_param = params[++i];
          executed = traverse(cur_layer->inTree, next_param, last_param, true);
        }
        else {
          executed = traverse(cur_layer->inTree, next_param, next_param, false);
        }
      }
    }
    // object will be looked for in current layer of abstraction
    else {
      next_layer = getPtr(cur_layer->inTree, params[i]);
      if (next_layer == NULL) {
        executed = false;
      }
    }
  }

  return executed;
}
