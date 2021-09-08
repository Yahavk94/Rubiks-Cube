#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Dimension.h"
#include "Operator.h"
#include "Node.h"

#define BUFFER_SIZE 1024
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
 * This function initializes and returns the root node of the search graph.
 */
struct Node *init_from_file() {
    const char *input_file_name = "Input.txt";
    FILE *fp = fopen(input_file_name, "r");
    if (fp == NULL) {
        perror(input_file_name);
        exit(EXIT_FAILURE);
    }

    struct Node *root = malloc(sizeof(struct Node));
    if (root == NULL) {
        perror("INIT_FROM_FILE");
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    root->operator = NONE;
    root->parent = NULL;

    char buffer[BUFFER_SIZE];
    size_t input_verifier[NUM_OF_FACES] = {0};

    const char *delim = "[,]\n";

    size_t i = 0;
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        const char *sticker = strtok(buffer, delim);

        while (sticker != NULL) {
            const size_t index = char_to_index(sticker[0]);
            if (index != ERROR) {
                root->state[i++] = sticker[0];
                input_verifier[index]++;
            }

            sticker = strtok(NULL, delim);
        }
    }

    fclose(fp);

    for (size_t i = 0; i < NUM_OF_FACES; i++) /* verify the input */ {
        if (input_verifier[i] != FACE_SIZE) {
            puts("INVALID INPUT");
            free(root);
            exit(EXIT_FAILURE);
        }
    }

    return root;
}
