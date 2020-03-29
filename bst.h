#ifndef BST_H
#define BST_H

// struct Node keeps:
// - name of the objects
// - pointer to its inner layer
// - pointer to left and right son in current layer of abstraction
struct Node;

typedef struct Node* Tree;

struct Node {
  char *name;
  Tree inTree;
  Tree left, right;
};

// checks whether object with name [x] exists in layer [t],
// if so returns pointer to it
Tree getPtr(Tree t, char *x);

// checks whether object with name [x], including in some of its inner layers
// object named [y], exists in some inner layer of [t], in case another is true;
// otherwise just checks if object with name [x] is in some inner layer of [t]
bool traverse(Tree t, char *x, char *y, bool another);

// inserts object [x] to the layer represented by [treePtr],
// in case we need to add another layer return the pointer to the added object
Tree insert(Tree *treePtr, char *x);

// prints all names of objects found in the layer [t]
void printAll(Tree t);

// removes all objects alongside with their inner layers from layer [t],
// as well as object representing layer [t]
void removeAll(Tree t);

// removes object with name [x], from layer represented by [treePtr]
void removeVal(Tree *treePtr, char *x);

#endif
