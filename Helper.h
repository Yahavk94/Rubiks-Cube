/**
 * This header file represents the functions which are used by the services.
 * @author Yahav Karpel
 */

#ifndef HELPER_H
#define HELPER_H

/**
 * This function returns true if the expansion based on the specified operators is redundant.
 */
bool is_redundant(const enum Operator node_to_expand_operator, const enum Operator op);

#endif
