## Introduction
Rubik's Cube is a 3D puzzle with six faces covered by a square number of stickers, each of one of 6 possible colors.
For the cube to be solved, each face must be returned to have only one color.

## Description
Assuming all faces are the same size and contain 9 stickers, this project uses Iterative Deepening A* algorithm to find a sequence of primitive steps, with a **minimal cost of moves** that will lead us from the initial node to the goal node.

## Installation
- Clone this repository.
- Open the attached input file without generating spaces and new lines, or deleting parentheses and commas.
- Select a random face, which will form the reference point of the cube.
- Starting from the top left corner towards the bottom right corner, insert the stickers of the current face into the ith line of the input file, row by row and from left to right, according to the given format.
- Rotate the entire cube 90 degrees downwards, so that the top face becomes the front face.
- Repeat bullets 4 and 5 until reaching the reference point.
- Rotate the entire cube 90 degrees to the right, so that the left face becomes the front face.
- Follow bullet number 4.
- Rotate the entire cube 180 degrees to the left, so that the back face becomes the front face.
- Follow bullet number 4.

Note that the input of a particular color is represented by the uppercase letter of its prefix, i.e. W refers to white, G refers to green, Y refers to yellow, B refers to blue, R refers to red and O refers to orange.

## Usage
```ruby
make
./Rubiks
```

## Improvements
Since the number of possible nodes is enormous, Iterative Deepening A* algorithm yields the optimal solution path for any node that is not too far from the goal, within a reasonable amount of time. Although this code is far from perfect, it is a step in the right direction.

## References
- R. E. Korf, "Finding Optimal Solutions to Rubik's Cube Using Pattern Databases", American Association for Artificial Intelligence (AAAI), pp. 700-705, 1997.

## License
[MIT](https://github.com/Yahavk94/Rubiks-Cube/blob/master/LICENSE)