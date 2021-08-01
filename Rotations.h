/**
 * This header file represents the rotations on the cube.
 * @author Yahav Karpel
 */

#ifndef ROTATIONS_H
#define ROTATIONS_H

/**
 * This function rotates the left face of the specified state by 90 degrees.
 */
void rotate_left_face(char *const state, const bool clockwise);

/**
 * This function rotates the top face of the specified state by 90 degrees.
 */
void rotate_top_face(char *const state, const bool clockwise);

/**
 * This function rotates the front face of the specified state by 90 degrees.
 */
void rotate_front_face(char *const state, const bool clockwise);

/**
 * This function rotates the right face of the specified state by 90 degrees.
 */
void rotate_right_face(char *const state, const bool clockwise);

/**
 * This function rotates the bottom face of the specified state by 90 degrees.
 */
void rotate_bottom_face(char *const state, const bool clockwise);

/**
 * This function rotates the back face of the specified state by 90 degrees.
 */
void rotate_back_face(char *const state, const bool clockwise);

/**
 * This function rotates the left face of the specified state by 180 degrees.
 */
void rotate_L2(char *const state);

/**
 * This function rotates the top face of the specified state by 180 degrees.
 */
void rotate_U2(char *const state);

/**
 * This function rotates the front face of the specified state by 180 degrees.
 */
void rotate_F2(char *const state);

/**
 * This function rotates the right face of the specified state by 180 degrees.
 */
void rotate_R2(char *const state);

/**
 * This function rotates the bottom face of the specified state by 180 degrees.
 */
void rotate_D2(char *const state);

/**
 * This function rotates the bottom face of the specified state by 180 degrees.
 */
void rotate_B2(char *const state);

#endif
