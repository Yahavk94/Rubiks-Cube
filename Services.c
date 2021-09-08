#include <search.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Dimension.h"
#include "Operator.h"
#include "Node.h"
#include "Services.h"
#include "Helper.h"

void free_branch_and_terminate(struct Node *deepest_node);

bool is_goal(const char *const state) {
    for (size_t face = 0; face < CUBE_SIZE; face += FACE_SIZE) {
        for (size_t i = 1; i < FACE_SIZE; i++) {
            if (state[face + i] != state[face]) {
                return false;
            }
        }
    }

    return true;
}

struct Node *expand_node(struct Node *node_to_expand, const enum Operator op) {
    if (is_redundant(node_to_expand->operator, op)) {
        return NULL;
    }

    struct Node *new_node = malloc(sizeof(struct Node));
    if (new_node == NULL) {
        perror("EXPAND_NODE");
        hdestroy();
        free_branch_and_terminate(node_to_expand);
    }

    // new_node is an expansion of node_to_expand by op
    new_node->operator = op;
    new_node->parent = node_to_expand;

    // a deep copy
    memcpy(new_node->state, node_to_expand->state, sizeof(new_node->state));

    switch (op) /* update the state of the new node */ {
    case L:
        rotate_left_face(new_node->state, true);
        break;

    case U:
        rotate_top_face(new_node->state, true);
        break;

    case F:
        rotate_front_face(new_node->state, true);
        break;

    case R:
        rotate_right_face(new_node->state, true);
        break;

    case D:
        rotate_bottom_face(new_node->state, true);
        break;

    case B:
        rotate_back_face(new_node->state, true);
        break;
    
    case Li:
        rotate_left_face(new_node->state, false);
        break;
    
    case Ui:
        rotate_top_face(new_node->state, false);
        break;
    
    case Fi:
        rotate_front_face(new_node->state, false);
        break;
    
    case Ri:
        rotate_right_face(new_node->state, false);
        break;
    
    case Di:
        rotate_bottom_face(new_node->state, false);
        break;
    
    case Bi:
        rotate_back_face(new_node->state, false);
        break;

    case L2:
        rotate_L2(new_node->state);
        break;

    case U2:
        rotate_U2(new_node->state);
        break;

    case F2:
        rotate_F2(new_node->state);
        break;

    case R2:
        rotate_R2(new_node->state);
        break;

    case D2:
        rotate_D2(new_node->state);
        break;

    case B2:
        rotate_B2(new_node->state);
        break;

    default: // should never reach here
        puts("INVALID OPERATOR");
        hdestroy();
        free_branch_and_terminate(new_node);
    }

    return new_node;
}
