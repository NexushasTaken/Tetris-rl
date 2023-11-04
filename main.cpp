#include <chrono>
#include <iostream>
#include <raylib.h>
#include "tetris.hpp"

int main() {
  int mino_size = 20;
  const int rows = 20;
  const int columns = 10;
  int width = mino_size*columns;
  int height = (mino_size/2 + mino_size*rows);
  float padding = width/2.0f;
  Vector2 offset = { (float)padding, padding };
  width += padding*2;
  height += padding*2;

  InitWindow(width, height, "Tetris");
  SetWindowState(FLAG_WINDOW_RESIZABLE);
  Tetris tetris(mino_size, offset);

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
