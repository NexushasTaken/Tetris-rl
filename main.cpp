#include <iostream>
#include <raylib.h>
#include "tetrimino.hpp"
#include "tetris_matrix.hpp"

using std::cout, std::endl;

int main() {
  int mino_size = 20;

  InitWindow(mino_size*10, mino_size/2 + mino_size*20, "Tetris");
  SetWindowState(FLAG_WINDOW_RESIZABLE);
  TMatrix matrix;

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(WHITE);
    matrix.draw(0, 0, mino_size);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
