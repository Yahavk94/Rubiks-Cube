/**
 * This struct represents a node in the search graph.
 * DO NOT MODIFY THIS FILE!
 * @author Yahav Karpel
 */

#ifndef NODE_H
#define NODE_H

struct Node {
    enum Operator operator;
    struct Node *parent;

    char state[CUBE_SIZE];
};

#endif
