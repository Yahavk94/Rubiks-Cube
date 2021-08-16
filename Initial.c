#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Dimension.h"
#include "Operator.h"
#include "Node.h"

#define ERROR 404

/**
 * This function returns the index corresponding to the specified character.
 */
static size_t char_to_index(const char ch) {
    switch (ch) {
    case 'W':
        return 0;
    case 'G':
        return 1;
    case 'Y':
        return 2;
    case 'B':
        return 3;
    case 'R':
        return 4;
    case 'O':
        return 5;
    default:
        return ERROR;
    }
}

/**
 * This function initializes and returns the initial node.
 */
struct Node *init_from_file() {
    const char *const input_file_name = "Input.txt";
    FILE *fp = fopen(input_file_name, "r");
    if (fp == NULL) {
        perror(input_file_name);
        exit(EXIT_FAILURE);
    }

    struct Node *const initial_node = malloc(sizeof(struct Node));
    if (initial_node == NULL) {
        perror("INIT_FROM_FILE");
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    initial_node->operator = NONE;
    initial_node->parent = NULL;

    char input[CUBE_SIZE];
    size_t input_verifier[NUM_OF_FACES] = {0};

    const char *const delim = "[,]\n";

    for (size_t face = 0; face < CUBE_SIZE; face += FACE_SIZE) /* initialize the initial state */ {
        if (fgets(input, sizeof(input), fp) == NULL) {
            break;
        }

        const char *sticker = strtok(input, delim);

        for (size_t i = 0; i < FACE_SIZE; i++) {
            const size_t index = char_to_index(sticker[0]);
            if (index != ERROR) {
                initial_node->state[face + i] = sticker[0];
                input_verifier[index]++;
            }

            sticker = strtok(NULL, delim);
        }
    }

    fclose(fp);

    for (size_t i = 0; i < NUM_OF_FACES; i++) /* verify the input */ {
        if (input_verifier[i] != FACE_SIZE) {
            puts("INVALID INPUT");
            free(initial_node);
            exit(EXIT_FAILURE);
        }
    }

    return initial_node;
}
