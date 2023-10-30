#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <raylib.h>
#include "utils.h"
#include "grid.h"

void dpyGrid(int **grid, int length) {
  int i, j;
  printf("display: \n");
  for (i = 0; i < length; i++) {
    for (j = 0; j < length; j++) {
      printf("%02d, ", grid[i][j]);
    }
    putchar('\n');
  }
  putchar('\n');
}

void addNumGrid(int **grid, int length) {
  int i, j, count;
  count = 1;
  for (i = 0; i < length; i++) {
    for (j = 0; j < length; j++) {
      grid[i][j] = count++;
    }
  }
}

int main() {
  int length = 6;
  int **grid = newGrid(length, length);
  addNumGrid(grid, length);

  dpyGrid(grid, length);
  rotateCCW(grid, length);
  rotateCCW(grid, length);
  dpyGrid(grid, length);

  freeGrid(&grid, length);
  return 0;
}
