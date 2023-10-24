#include <stdlib.h>
#include <math.h>
#include "utils.h"
#include "grid.h"

int** newGrid(int rows, int cols) {
  int **grid;

  grid = calloc(rows, sizeof(int*));
  for (int i = 0; i < rows; i++) {
    grid[i] = calloc(cols, sizeof(int));
  }
  return grid;
}

void freeGrid(int ***grid, int rows) {
  for (int i = 0; i < rows; i++) {
    free((*grid)[i]);
  }
  free(*grid);
  *grid = NULL;
}

void flip(int **grid, int length, int x) {
  int i, j, half;

  half = (int)floor(length/2.0);
  for (i = 0; i < half; i++) {
    for (j = 0; j < length; j++) {
      if (x) {
        swap(&grid[j][i], &(grid[j][length-i-1]));
      } else {
        swap(&grid[i][j], &(grid[length-i-1][j]));
      }
    }
  }
}

void transpose(int ***grid, int length, bool back) {
  int **new = malloc(sizeof(int*) * length);
  for (int i = 0; i < length; i++) {
    new[i] = malloc(sizeof(int) * length);
  }
  for (int i = 0; i < length; i++) {
    for (int j = 0; j < length; j++) {
      if (back) {
        new[j][i] = (*grid)[i][j];
      } else {
        new[j][i] = (*grid)[length-i-1][length-j-1];
      }
    }
  }
  freeGrid(grid, length);
  *grid = new;
}
