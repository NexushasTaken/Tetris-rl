#include <iostream>
#include <raylib.h>
#include "timer.hpp"
#include "tetris.hpp"

Tetris::Tetris()
  : mino_size(20),
    offset(CLITERAL(Vector2){100, 100}) {

}

void Tetris::draw() {
  float total_height = mino_size/2.0f + mino_size*20.0f;
  float total_width  = mino_size*10.0f;
  Rectangle rect = {
    .x = this->offset.x,
    .y = this->offset.y,
    .width = total_width,
    .height = total_height,
  };
  // ---- BufferBorder ----
  DrawRectangleLinesEx(rect, 1, BLACK);

  // ---- BufferVerticalLines ----
  rect.width = 2;
  for (int i = 0; i < this->maytrix.buffer_area[0].size(); i++) {
    if (!i || i >= this->maytrix.buffer_area.size()-1) {
      continue;
    }
    rect.x = i * mino_size - 1 + this->offset.x;
    DrawRectangleRec(rect, BLACK);
  }

  // ---- BufferHorizontalLines ----
  rect.x = this->offset.x;
  rect.width = total_width;
  rect.height = 2;
  for (int i = 0; i < 20; i++) {
    rect.y = i * mino_size + (mino_size/2) - 1 + this->offset.y;
    DrawRectangleRec(rect, BLACK);
  }

  // Test Controls
  static int shape = 1;
  if (IsKeyPressed(KEY_C)) { shape--; }
  if (IsKeyPressed(KEY_V)) { shape++; }
  if (shape >= (int)TetriminoShape::Last) {
    shape = 1;
  }
  if (shape <= 0) {
    shape = (int)TetriminoShape::Last-1;
  }
  if (IsKeyPressed(KEY_C) || IsKeyPressed(KEY_V)) {
    this->maytrix.tetrimino.swap((TetriminoShape)shape);
  }
  if (IsKeyPressed(KEY_Z)) { this->maytrix.tetriminoRotate(Rotate::CCW); }
  if (IsKeyPressed(KEY_X)) { this->maytrix.tetriminoRotate(Rotate::CW); }

  if (IsKeyPressed(KEY_UP)) { this->maytrix.tetriminoMove(Direction::Up); }
  if (IsKeyPressed(KEY_DOWN)) { this->maytrix.tetriminoMove(Direction::Down); }
  if (IsKeyPressed(KEY_LEFT)) { this->maytrix.tetriminoMove(Direction::Left); }
  if (IsKeyPressed(KEY_RIGHT)) { this->maytrix.tetriminoMove(Direction::Right); }

  if (IsKeyPressed(KEY_SPACE)) { this->maytrix.hardDrop(); }

  // ---- BufferMinos ----
  for (auto [row, col, mino] : this->maytrix) {
    if (mino) {
      DrawRectangleV(
          this->calculateMinoPosition(this->offset.x, this->offset.x, col, row, mino_size),
              CLITERAL(Vector2){mino_size, mino_size}, MINO_DATA(mino).color);
    }
  }

  // ---- Tetrimino ----
  auto tetrimino_draw = [this]() {
    // char buffer[12];
    for (auto [row, col, mino] : this->maytrix.tetrimino) {
      Vector2 pos =
        this->calculateMinoPosition(
          this->offset.x, this->offset.y,
          col + this->maytrix.tetrimino.column, row + this->maytrix.tetrimino.row,
          mino_size);
      if (mino) {
        DrawRectangleV(pos, CLITERAL(Vector2)({mino_size, mino_size}), this->maytrix.tetrimino.color);
      }
      // sprintf(buffer, "%d:%d", col + this->column, row + this->row);
      // DrawText(buffer, pos.x+2, pos.y+2, 12, GRAY);
    }
  };
  tetrimino_draw();

  // ---- Ghost Tetrimino ----
  int move_count = this->maytrix.drop();
  if (move_count) {
    this->maytrix.tetrimino.color.a = 100;
    tetrimino_draw();
    this->maytrix.tetrimino.color.a = 255;
    this->maytrix.undrop(move_count);
  }
}

Vector2 Tetris::calculateMinoPosition(
    float offx, float offy,
    int column, int row,
    float mino_size) {
  float x = offx;
  float y = offy;
  y += mino_size/2.0f + mino_size*20.0f;
  y -= mino_size*row + mino_size;
  x += mino_size*column;
  return CLITERAL(Vector2){x, y};
}

