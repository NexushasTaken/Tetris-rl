#ifndef GRID_H
#define GRID_H

#include <stdbool.h>

typedef struct _Grid {
  int **data;
  int rows;
  int cols;
} Grid;

Grid* newGrid(int rows, int cols);
void freeGrid(Grid **grid);
void gridSwapData(Grid *grid, int **new_data, int rows, int cols);

// flip*, transpose*, rotate* functions/macros will only work for equal rows and columns of the grid
void flip(Grid *grid, int x);
#define flipX(grid) flip(grid, true);
#define flipY(grid) flip(grid, false);

void transpose(Grid **grid, bool back);
#define transposeB(grid) transpose(grid, false);
#define transposeF(grid) transpose(grid, true);

#define rotateCW(grid, length)  { transposeF(&grid, length); flipY(grid, length); }
#define rotateCCW(grid, length) { transposeB(&grid, length); flipY(grid, length); }

#endif // GRID_H
