#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Dimension.h"
#include "Operator.h"
#include "Node.h"

#define MAX_LENGTH 1000

static char *operator_to_str[] = {
    "L",
    "U",
    "F",
    "R",
    "D",
    "B",
    "Li",
    "Ui",
    "Fi",
    "Ri",
    "Di",
    "Bi",
    "L2",
    "U2",
    "F2",
    "R2",
    "D2",
    "B2"
};

struct Node *init_from_file();
struct Node *ida_star(struct Node *root);

/**
 * This function frees up the current branch and terminates the program.
 */
void free_branch_and_terminate(struct Node *deepest_node) {
    while (deepest_node != NULL) {
        struct Node *to_free = deepest_node;
        deepest_node = deepest_node->parent;
        free(to_free);
    }

    exit(EXIT_FAILURE);
}

/**
 * This function runs the cube solver.
 */
void run() {
    clock_t start = clock();

    struct Node *root = init_from_file();
    struct Node *result = ida_star(root);
    puts("SEARCH COMPLETED!");

    const char *output_file_name = "Output.txt";
    FILE *fp = fopen(output_file_name, "w");
    if (fp == NULL) {
        perror(output_file_name);
        if (result == NULL) {
            free(root);
            exit(EXIT_FAILURE);
        }

        free_branch_and_terminate(result);
    }

    if (result == NULL) {
        fprintf(fp, "NO PATH\n");
    } else if (result != root) {
        char *sequence_of_operators[MAX_LENGTH];
        size_t i = 0;

        do {
            sequence_of_operators[i++] = operator_to_str[result->operator];
            struct Node *to_free = result;
            result = result->parent;
            free(to_free);
        } while (result != root);

        while (i > 1) {
            fprintf(fp, "%s-", sequence_of_operators[--i]);
        }

        fprintf(fp, "%s\n", sequence_of_operators[0]);
    }

    free(root);

    fprintf(fp, "%.5f seconds", ((double)(clock() - start)) / CLOCKS_PER_SEC);
    fclose(fp);

    puts("PLEASE CHECK THE OUTPUT FILE");
}
