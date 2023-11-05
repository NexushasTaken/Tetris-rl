#include <chrono>
#include <iostream>
#include <raylib.h>
#include "tetris.hpp"

int main() {
  int mino_size = 18;
  const int rows = 20;
  const int columns = 10;
  int field_width = mino_size*columns;
  int field_height = mino_size/2 + mino_size*rows;
  float pad_lr = mino_size*6;
  Vector2 field_offset = { pad_lr, 0, };

  InitWindow(field_width + pad_lr*2, field_height, "Tetris");
  SetWindowState(FLAG_WINDOW_RESIZABLE);
  Tetris tetris(mino_size, field_offset);

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
