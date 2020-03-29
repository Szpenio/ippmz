#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "bst.h"

// auxiliary strcutre to store name and pointer to inner Tree of certain object
struct Keep;

typedef struct Keep* MoveUp;

struct Keep {
  char *name;
  Tree inTree;
};

// checks whether object with name [x] exists in layer [t]
Tree getPtr(Tree t, char *x) {
  if (t == NULL) {
    return NULL;
  }
  else if (strcmp(x, t->name) > 0) {
    return getPtr(t->left, x);
  }
  else if (strcmp(x, t->name) < 0) {
    return getPtr(t->right, x);
  }

  return t;
}

// traverses inner layers of [t], searching for [x] and/or [y]
// depending on argument another is true or not
bool traverse(Tree t, char *x, char *y, bool another) {
  bool found = false;

  if (t == NULL) {
    return found;
  }
  else {
    if (another) {
      found = traverse(t->inTree, x, y, !another);
    }
    else if (getPtr(t->inTree, y) != NULL) {
      found = true;
    }
    return found || traverse(t->left, x, y, another)
          || traverse(t->right, x, y, another);
  }
}

// inserts object [x] to the layer represented by [treePtr]
Tree insert(Tree *treePtr, char *x) {
  Tree t = *treePtr;

  if (t == NULL) {
    t = malloc(sizeof(struct Node));
    if (t == NULL) {
      exit(1);
    }

    t->name = strdup(x);
    if (t->name == NULL) {
      exit(1);
    }
    t->inTree = NULL;
    t->left = t->right = NULL;
    *treePtr = t;
  }
  else if (strcmp(x, t->name) > 0) {
    return insert(&t->left, x);
  }
  else if (strcmp(x, t->name) < 0) {
    return insert(&t->right, x);
  }
  return t;
}

// prints all names of objects found in the layer [t]
void printAll(Tree t) {
  if (t != NULL) {
    printAll(t->right);
    puts(t->name);
    printAll(t->left);
  }
}

// removes all objects alongside with their inner layers from layer [t],
// as well as object representing layer [t]
void removeAll(Tree t) {
  if (t != NULL) {
    removeAll(t->inTree);
    removeAll(t->left);
    removeAll(t->right);
    free(t->name);
    free(t);
  }
}

// removes object with lexicographically least name,
// keeping its name and pointer to its inner layer
static MoveUp removeMin(Tree *treePtr) {
  Tree t = *treePtr;
  MoveUp node_up = NULL;

  if (t->left == NULL) {
    node_up = malloc(sizeof(struct Keep));
    if (node_up == NULL) {
      exit(1);
    }

    node_up->name = t->name;
    node_up->inTree = t->inTree;
    *treePtr = t->right;
    free(t);

    return node_up;
  }
  else {
    return removeMin(&t->left);
  }
}

// removes object with name [x], from layer represented by [treePtr]
void removeVal(Tree *treePtr, char *x) {
  Tree t = *treePtr;

  if (t != NULL) {
    if (strcmp(x, t->name) > 0) {
      removeVal(&t->left, x);
    }
    else if (strcmp(x, t->name) < 0) {
      removeVal(&t->right, x);
    }
    else {
      if (t->right == NULL) {
        *treePtr = t->left;
        removeAll(t->inTree);
        free(t->name);
        free(t);
      }
      else {
        MoveUp down = removeMin(&t->right);
        removeAll(t->inTree);
        free(t->name);

        t->name = down->name;
        t->inTree = down->inTree;
        free(down);
      }
    }
  }
}
