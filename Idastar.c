#include <search.h>
#include <stdbool.h>
#include <stdlib.h>
#include "Dimension.h"
#include "Operator.h"
#include "Node.h"
#include "Services.h"

#define EXPANSION_COST 1

static size_t bound;
static struct Node *result = NULL;

size_t heuristic_evaluation(const char *const state);

static size_t search(struct Node *current_node, const size_t path_cost) {
    const size_t f = path_cost + heuristic_evaluation(current_node->state);
    if (f > bound) /* do not exceed the current bound */ {
        return f;
    }

    if (is_goal(current_node->state)) /* the goal was found */ {
        result = current_node;
        return FOUND;
    }

    // should be set to a strict upper bound
    size_t min_f = UPPER_BOUND;

    for (size_t i = 0; i < NUM_OF_OPERATORS; i++) /* generate the next possible nodes */ {
        struct Node *new_node = expand_node(current_node, i);
        if (new_node == NULL) {
            continue;
        }

        const ENTRY item = {
            new_node->state, new_node
        };

        ENTRY *found_item = hsearch(item, FIND);
        if (found_item == NULL) {
            hsearch(item, ENTER);
        } else {
            if (found_item->data != NULL) /* a loop has been detected */ {
                free(new_node);
                continue;
            }

            found_item->data = new_node;
        }

        // recurse
        const size_t t = search(new_node, path_cost + EXPANSION_COST);

        if (t == FOUND) {
            return FOUND;
        } if (t < min_f) {
            min_f = t;
        }

        // remove traces
        found_item = hsearch(item, FIND);
        free(found_item->data);
        found_item->data = NULL;
    }

    return min_f;
}

struct Node *ida_star(struct Node *initial_node) {
    hcreate(HASH_TABLE_SIZE);

    const ENTRY item = {
        initial_node->state, initial_node
    };

    hsearch(item, ENTER);

    // initialize the bound
    bound = heuristic_evaluation(initial_node->state);

    while (true) {
        const size_t t = search(initial_node, 0);
        if (t == FOUND || t == UPPER_BOUND) /* end of search */ {
            break;
        }

        // increase the bound
        bound = t;
    }

    hdestroy();

    if (result != NULL) {
        struct Node *goal_node = result;
        result = NULL;
        return goal_node;
    }

    return NULL;
}
