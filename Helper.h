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

/**
 * This function rotates the left face of the specified state by 90 degrees.
 */
void rotate_left_face(char *state, const bool clockwise);

/**
 * This function rotates the top face of the specified state by 90 degrees.
 */
void rotate_top_face(char *state, const bool clockwise);

/**
 * This function rotates the front face of the specified state by 90 degrees.
 */
void rotate_front_face(char *state, const bool clockwise);

/**
 * This function rotates the right face of the specified state by 90 degrees.
 */
void rotate_right_face(char *state, const bool clockwise);

/**
 * This function rotates the bottom face of the specified state by 90 degrees.
 */
void rotate_bottom_face(char *state, const bool clockwise);

/**
 * This function rotates the back face of the specified state by 90 degrees.
 */
void rotate_back_face(char *state, const bool clockwise);

/**
 * This function rotates the left face of the specified state by 180 degrees.
 */
void rotate_L2(char *state);

/**
 * This function rotates the top face of the specified state by 180 degrees.
 */
void rotate_U2(char *state);

/**
 * This function rotates the front face of the specified state by 180 degrees.
 */
void rotate_F2(char *state);

/**
 * This function rotates the right face of the specified state by 180 degrees.
 */
void rotate_R2(char *state);

/**
 * This function rotates the bottom face of the specified state by 180 degrees.
 */
void rotate_D2(char *state);

/**
 * This function rotates the bottom face of the specified state by 180 degrees.
 */
void rotate_B2(char *state);

#endif
