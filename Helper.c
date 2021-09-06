#include <stdbool.h>
#include <stddef.h>
#include "Dimension.h"
#include "Face.h"
#include "Operator.h"
#include "Helper.h"

bool is_redundant(const enum Operator node_to_expand_operator, const enum Operator op) {
    switch (node_to_expand_operator) /* according to Korf's paper (see references) */ {
    case L:
    case Li:
    case L2:
        return op == L || op == Li || op == L2;

    case U:
    case Ui:
    case U2:
        return op == U || op == Ui || op == U2;

    case F:
    case Fi:
    case F2:
        return op == F || op == Fi || op == F2;

    case R:
    case Ri:
    case R2:
        return (op == R || op == Ri || op == R2) || (op == L || op == Li || op == L2);

    case D:
    case Di:
    case D2:
        return (op == D || op == Di || op == D2) || (op == U || op == Ui || op == U2);

    case B:
    case Bi:
    case B2:
        return (op == B || op == Bi || op == B2) || (op == F || op == Fi || op == F2);

    default: // node_to_expand is the root
        return false;
    }
}

/**
 * This function returns the corresponding sticker in the cube.
 */
static inline size_t get_sticker(const enum Face f, const size_t r, const size_t c) {
    return FACE_SIZE * f + N * r + c;
}

static void swap(char *state, const size_t a, const size_t b, const size_t c, const size_t d) {
    const char temp = state[a];
    state[a] = state[b];
    state[b] = state[c];
    state[c] = state[d];
    state[d] = temp;
}

static void rotate_face(char *state, const enum Face face_to_rotate, const bool clockwise) {
    for (size_t i = 0; i < N - 1; i++) {
        const size_t a = get_sticker(face_to_rotate, 0, i);
        const size_t b = get_sticker(face_to_rotate, N - 1 - i, 0);
        const size_t c = get_sticker(face_to_rotate, N - 1, N - 1 - i);
        const size_t d = get_sticker(face_to_rotate, i, N - 1);

        if (clockwise) {
            swap(state, a, b, c, d);
        } else {
            swap(state, a, d, c, b);
        }
    }
}

void rotate_left_face(char *state, const bool clockwise) {
    for (size_t i = 0; i < N; i++) {
        const size_t front_face_sticker = get_sticker(FRONT, i, 0);
        const size_t bottom_face_sticker = get_sticker(BOTTOM, i, 0);
        const size_t back_face_sticker = get_sticker(BACK, i, 0);
        const size_t top_face_sticker = get_sticker(TOP, i, 0);

        if (clockwise) {
            swap(state, front_face_sticker, top_face_sticker, back_face_sticker, bottom_face_sticker);
        } else {
            swap(state, front_face_sticker, bottom_face_sticker, back_face_sticker, top_face_sticker);
        }
    }

    rotate_face(state, LEFT, clockwise);
}

void rotate_top_face(char *state, const bool clockwise) {
    for (size_t i = 0; i < N; i++) {
        const size_t front_face_sticker = get_sticker(FRONT, 0, N - 1 - i);
        const size_t right_face_sticker = get_sticker(RIGHT, 0, N - 1 - i);
        const size_t back_face_sticker = get_sticker(BACK, N - 1, i);
        const size_t left_face_sticker = get_sticker(LEFT, 0, N - 1 - i);

        if (clockwise) {
            swap(state, front_face_sticker, right_face_sticker, back_face_sticker, left_face_sticker);
        } else {
            swap(state, front_face_sticker, left_face_sticker, back_face_sticker, right_face_sticker);
        }
    }

    rotate_face(state, TOP, clockwise);
}

void rotate_front_face(char *state, const bool clockwise) {
    for (size_t i = 0; i < N; i++) {
        const size_t top_face_sticker = get_sticker(TOP, N - 1, i);
        const size_t left_face_sticker = get_sticker(LEFT, N - 1 - i, N - 1);
        const size_t bottom_face_sticker = get_sticker(BOTTOM, 0, N - 1 - i);
        const size_t right_face_sticker = get_sticker(RIGHT, i, 0);

        if (clockwise) {
            swap(state, top_face_sticker, left_face_sticker, bottom_face_sticker, right_face_sticker);
        } else {
            swap(state, top_face_sticker, right_face_sticker, bottom_face_sticker, left_face_sticker);
        }
    }

    rotate_face(state, FRONT, clockwise);
}

void rotate_right_face(char *state, const bool clockwise) {
    for (size_t i = 0; i < N; i++) {
        const size_t front_face_sticker = get_sticker(FRONT, i, N - 1);
        const size_t bottom_face_sticker = get_sticker(BOTTOM, i, N - 1);
        const size_t back_face_sticker = get_sticker(BACK, i, N - 1);
        const size_t top_face_sticker = get_sticker(TOP, i, N - 1);

        if (clockwise) {
            swap(state, front_face_sticker, bottom_face_sticker, back_face_sticker, top_face_sticker);
        } else {
            swap(state, front_face_sticker, top_face_sticker, back_face_sticker, bottom_face_sticker);
        }
    }

    rotate_face(state, RIGHT, clockwise);
}

void rotate_bottom_face(char *state, const bool clockwise) {
    for (size_t i = 0; i < N; i++) {
        const size_t front_face_sticker = get_sticker(FRONT, N - 1, N - 1 - i);
        const size_t right_face_sticker = get_sticker(RIGHT, N - 1, N - 1 - i);
        const size_t back_face_sticker = get_sticker(BACK, 0, i);
        const size_t left_face_sticker = get_sticker(LEFT, N - 1, N - 1 - i);

        if (clockwise) {
            swap(state, front_face_sticker, left_face_sticker, back_face_sticker, right_face_sticker);
        } else {
            swap(state, front_face_sticker, right_face_sticker, back_face_sticker, left_face_sticker);
        }
    }

    rotate_face(state, BOTTOM, clockwise);
}

void rotate_back_face(char *state, const bool clockwise) {
    for (size_t i = 0; i < N; i++) {
        const size_t top_face_sticker = get_sticker(TOP, 0, i);
        const size_t left_face_sticker = get_sticker(LEFT, N - 1 - i, 0);
        const size_t bottom_face_sticker = get_sticker(BOTTOM, N - 1, N - 1 - i);
        const size_t right_face_sticker = get_sticker(RIGHT, i, N - 1);

        if (clockwise) {
            swap(state, top_face_sticker, right_face_sticker, bottom_face_sticker, left_face_sticker);
        } else {
            swap(state, top_face_sticker, left_face_sticker, bottom_face_sticker, right_face_sticker);
        }
    }

    rotate_face(state, BACK, clockwise);
}

void rotate_L2(char *state) {
    for (size_t i = 0; i < 2; i++) {
        rotate_left_face(state, true);
    }
}

void rotate_U2(char *state) {
    for (size_t i = 0; i < 2; i++) {
        rotate_top_face(state, true);
    }
}

void rotate_F2(char *state) {
    for (size_t i = 0; i < 2; i++) {
        rotate_front_face(state, true);
    }
}

void rotate_R2(char *state) {
    for (size_t i = 0; i < 2; i++) {
        rotate_right_face(state, true);
    }
}

void rotate_D2(char *state) {
    for (size_t i = 0; i < 2; i++) {
        rotate_bottom_face(state, true);
    }
}

void rotate_B2(char *state) {
    for (size_t i = 0; i < 2; i++) {
        rotate_back_face(state, true);
    }
}
