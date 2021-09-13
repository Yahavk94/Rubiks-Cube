/**
 * This struct represents a node in the search graph.
 * DO NOT MODIFY THIS FILE!
 * @author Yahav Karpel
 */

#ifndef NODE_H
#define NODE_H

struct Node {
    // the parent node of this node
    struct Node *parent;

    // the operator that generated this node
    enum Operator operator;

    // the state of this node
    char state[CUBE_SIZE];
};

#endif
