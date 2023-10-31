#include <iostream>
#include <raylib.h>
#include "tetris.hpp"

int main() {
  int mino_size = 20;

  InitWindow(mino_size*10 * 2, (mino_size/2 + mino_size*20) * 2, "Tetris");
  SetWindowState(FLAG_WINDOW_RESIZABLE);
  Tetris tetris;

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(WHITE);
    tetris.draw();
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
