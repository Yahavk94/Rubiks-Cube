#include <search.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Dimension.h"
#include "Operator.h"
#include "Node.h"
#include "Services.h"
#include "Rotations.h"

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
    /* avoid redundant steps */ {
        bool redundant;
        switch (node_to_expand->operator) /* according to Korf's paper (see references) */ {
        case L:
        case L2:
        case Li:
            redundant = op == L || op == L2 || op == Li;
            break;

        case U:
        case U2:
        case Ui:
            redundant = op == U || op == U2 || op == Ui;
            break;

        case F:
        case F2:
        case Fi:
            redundant = op == F || op == F2 || op == Fi;
            break;

        case R:
        case R2:
        case Ri:
            redundant = (op == R || op == R2 || op == Ri) || (op == L || op == L2 || op == Li);
            break;

        case D:
        case D2:
        case Di:
            redundant = (op == D || op == D2 || op == Di) || (op == U || op == U2 || op == Ui);
            break;

        case B:
        case B2:
        case Bi:
            redundant = (op == B || op == B2 || op == Bi) || (op == F || op == F2 || op == Fi);
            break;

        default: // node_to_expand is the root
            redundant = false;
            break;
        }

        if (redundant) {
            return NULL;
        }
    }

    struct Node *const new_node = malloc(sizeof(struct Node));
    if (new_node == NULL) {
        perror("EXPAND_NODE");
        hdestroy();
        free_branch_and_terminate(node_to_expand);
    }

    new_node->operator = op;
    new_node->parent = node_to_expand;
    memcpy(new_node->state, node_to_expand->state, sizeof(new_node->state));

    switch (op) /* update the state of the generated node */ {
    case L:
        rotate_left_face(new_node->state, true);
        break;

    case Li:
        rotate_left_face(new_node->state, false);
        break;

    case U:
        rotate_top_face(new_node->state, true);
        break;

    case Ui:
        rotate_top_face(new_node->state, false);
        break;

    case F:
        rotate_front_face(new_node->state, true);
        break;

    case Fi:
        rotate_front_face(new_node->state, false);
        break;

    case R:
        rotate_right_face(new_node->state, true);
        break;

    case Ri:
        rotate_right_face(new_node->state, false);
        break;

    case D:
        rotate_bottom_face(new_node->state, true);
        break;

    case Di:
        rotate_bottom_face(new_node->state, false);
        break;

    case B:
        rotate_back_face(new_node->state, true);
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
