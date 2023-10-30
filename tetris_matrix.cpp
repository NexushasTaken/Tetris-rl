#include "tetris_matrix.hpp"

TMatrix::TMatrix() : tetrimino(TetriminoShape::T) {
  this->buffer_zone = MatrixDS(20, std::vector<int>(10));
}

void TMatrix::draw(float x, float y, float mino_size) {
  float total_height = mino_size/2.0f + mino_size*20.0f;
  float total_width  = mino_size*10.0f;
  Rectangle rect = {
    .x = x,
    .y = y,
    .width = total_width,
    .height = total_height,
  };
  DrawRectangleLinesEx(rect, 1, BLACK);

  rect.width = 2;
  for (int i = 0; i < this->buffer_zone[0].size(); i++) {
    if (!i || i >= this->buffer_zone.size()-1) {
      continue;
    }
    rect.x = i * mino_size - 1 + x;
    DrawRectangleRec(rect, BLACK);
  }

  rect.x = x;
  rect.width = total_width;
  rect.height = 2;
  for (int i = 0; i < this->buffer_zone.size(); i++) {
    rect.y = i * mino_size + (mino_size/2) - 1 + y;
    DrawRectangleRec(rect, BLACK);
  }

  if (IsKeyPressed(KEY_W)) { this->tetrimino.row++; }
  if (IsKeyPressed(KEY_S)) { this->tetrimino.row--; }
  if (IsKeyPressed(KEY_A)) { this->tetrimino.column--; }
  if (IsKeyPressed(KEY_D)) { this->tetrimino.column++; }
  tetrimino.draw(
      x + mino_size*this->tetrimino.column,
      y + total_height - mino_size*2 - mino_size*this->tetrimino.row,
      mino_size);
}

MatrixDSIterator TMatrix::begin() {
  return MatrixDSIterator(&this->buffer_zone);
}

MatrixDSIterator TMatrix::end() {
  return MatrixDSIterator(&this->buffer_zone, this->buffer_zone.size());
}
