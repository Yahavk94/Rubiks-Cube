/**
 * This header file represents the services which are used by the search algorithm.
 * @author Yahav Karpel
 */

#ifndef SERVICES_H
#define SERVICES_H

#define HASH_TABLE_SIZE 100000000
#define UPPER_BOUND 1000
#define FOUND 0
#define NUM_OF_OPERATORS NUM_OF_FACES * N

/**
 * This function returns true if the specified state is the goal state.
 */
bool is_goal(const char *const state);

/**
 * This function returns the node generated by the specified operator.
 */
struct Node *expand_node(struct Node *node_to_expand, const enum Operator op);

#endif