#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utils.h"
#include "grid.h"

Grid* newGrid(int rows, int cols) {
  Grid *grid;

  grid = calloc(rows, sizeof(Grid));
  grid->rows = rows;
  grid->cols = cols;

  grid->data = calloc(rows, sizeof(int*));
  for (int i = 0; i < rows; i++) {
    grid->data[i] = calloc(cols, sizeof(int));
  }
  return grid;
}

static void freeData(Grid *grid) {
  int i;
  for (i = 0; i < grid->rows; i++) {
    free(grid->data[i]);
  }
  free(grid->data);
  grid->data = NULL;
}

void freeGrid(Grid **grid) {
  freeData(*grid);
  free(*grid);
  *grid = NULL;
}

void gridSwapData(Grid *grid, int **new_data, int rows, int cols) {
  freeData(grid);
  grid->data = new_data;
  grid->rows = rows;
  grid->cols = cols;
}

void flip(Grid *grid, int x) {
  if (grid->rows != grid->cols) {
    fprintf(stderr, "rows(%d) and cols(%d) must be the same!", grid->rows, grid->cols);
  }
  int i, j, half, length, **data;

  data = grid->data;
  length = grid->rows;
  half = (int)floor(length/2.0);
  for (i = 0; i < half; i++) {
    for (j = 0; j < length; j++) {
      if (x) {
        swap(&data[j][i], &(data[j][length-i-1]));
      } else {
        swap(&data[i][j], &(data[length-i-1][j]));
      }
    }
  }
}

void transpose(Grid **_grid, bool back) {
  Grid *grid = *_grid;
  int **new, **data, i, j, length;

  length = grid->rows;
  data = grid->data;

  new = malloc(sizeof(int*) * length);
  for (i = 0; i < length; i++) {
    new[i] = malloc(sizeof(int) * length);
  }

  for (i = 0; i < length; i++) {
    for (j = 0; j < length; j++) {
      if (back) {
        new[j][i] = data[i][j];
      } else {
        new[j][i] = data[length-i-1][length-j-1];
      }
    }
  }
  freeGrid(&grid);
  gridSwapData(grid, new, length, length);
}
