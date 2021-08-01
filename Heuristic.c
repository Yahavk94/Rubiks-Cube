#include <stddef.h>
#include "Dimension.h"

#define CENTRE 4
#define EDGES_PER_FACE 4

static size_t max_misplaced_edges(const char *const state) {
    size_t max = 0;
    for (size_t face = 0; face < CUBE_SIZE; face += FACE_SIZE) {
        size_t count = 0;
        const char current_centre = state[face + CENTRE];

        for (size_t i = 1; i < FACE_SIZE; i += 2) {
            if (state[face + i] != current_centre) {
                count++;
            }
        }

        if (count == EDGES_PER_FACE) {
            return count;
        } if (count > max) {
            max = count;
        }
    }

    return max;
}

/**
 * This function calculates and returns the heuristic evaluation of the specified state.
 */
size_t heuristic_evaluation(const char *const state) {
    return max_misplaced_edges(state);
}
