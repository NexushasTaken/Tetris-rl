#include <chrono>
#include <iostream>
#include <raylib.h>
#include "tetris.hpp"

int main() {
  int mino_size = 20;
  int width = mino_size*10;
  int height = (mino_size/2 + mino_size*20);

  InitWindow(width, height, "Tetris");
  SetWindowState(FLAG_WINDOW_RESIZABLE);
  Tetris tetris;

  while (!WindowShouldClose()) {
    tetris.update();
    BeginDrawing();
    ClearBackground(WHITE);
    tetris.draw();
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
