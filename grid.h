#ifndef GRID_H
#define GRID_H

#include <stdbool.h>

int** newGrid(int rows, int cols);
void freeGrid(int ***grid, int rows);

// flip*, transpose*, rotate* functions/macros will only work for equal rows and columns of the grid
void flip(int **grid, int length, int x);
#define flipX(grid, length) flip(grid, length, true);
#define flipY(grid, length) flip(grid, length, false);

void transpose(int ***grid, int length, bool back);
#define transposeB(grid, length) transpose(grid, length, false);
#define transposeF(grid, length) transpose(grid, length, true);

#define rotateCW(grid, length)  { transposeF(&grid, length); flipY(grid, length); }
#define rotateCCW(grid, length) { transposeB(&grid, length); flipY(grid, length); }

#endif // GRID_H
