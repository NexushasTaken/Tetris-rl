#include <iostream>
#include <algorithm>
#include "tetris_matrix.hpp"

Maytrix::Maytrix() : tetrimino(TetriminoShape::O) {
  this->tetrimino.swap(TetriminoShape::O);
  this->buffer_area = BufferArea(24, std::vector<int>(10));
  // this->buffer_zone = {
  //   {1,1,1,2,3,4,4,5,5,6},
  //   {0,1,2,2,3,4,5,5,6,6},
  //   {0,0,0,2,3,4,0,0,6,3},
  //   {0,0,0,0,3,0,0,0,0,3},
  //   {0,0,0,0,0,0,0,0,0,3},
  //   {0,0,0,0,0,0,0,0,0,3},
  //   {0,0,0,0,0,0,0,0,0,0},
  //   {0,0,0,0,0,0,0,0,0,0},
  //   {0,0,0,0,0,0,0,0,0,0},
  //   {0,0,0,0,0,0,0,0,0,0},
  //   {0,0,0,0,0,0,0,0,0,0},
  //   {0,0,0,0,0,0,0,0,0,0},
  //   {0,0,0,0,0,0,0,0,0,0},
  //   {0,0,0,0,0,0,0,0,0,0},
  //   {0,0,0,0,0,0,0,0,0,0},
  //   {0,0,0,0,0,0,0,0,0,0},
  //   {0,0,0,0,0,0,0,0,0,0},
  //   {0,0,0,0,0,0,0,0,0,0},
  //   {0,0,0,0,0,0,0,0,0,0},
  //   {0,0,0,0,0,0,0,0,0,0},
  //   {0,0,0,0,0,0,0,0,0,0},
  //   {0,0,0,0,0,0,0,0,0,0},
  //   {0,0,0,0,0,0,0,0,0,0},
  //   {0,0,0,0,0,0,0,0,0,0},
  // };
}

void Maytrix::draw(float x, float y, float mino_size) {
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
  for (int i = 0; i < this->buffer_area[0].size(); i++) {
    if (!i || i >= this->buffer_area.size()-1) {
      continue;
    }
    rect.x = i * mino_size - 1 + x;
    DrawRectangleRec(rect, BLACK);
  }

  rect.x = x;
  rect.width = total_width;
  rect.height = 2;
  for (int i = 0; i < this->buffer_area.size()-4; i++) {
    rect.y = i * mino_size + (mino_size/2) - 1 + y;
    DrawRectangleRec(rect, BLACK);
  }

  static int shape = 1;
  if (IsKeyPressed(KEY_Q)) { shape--; }
  if (IsKeyPressed(KEY_E)) { shape++; }
  if (shape >= (int)TetriminoShape::Last) {
    shape = 1;
  }
  if (shape <= 0) {
    shape = (int)TetriminoShape::Last-1;
  }
  if (IsKeyPressed(KEY_E) || IsKeyPressed(KEY_Q)) {
    this->tetrimino.swap((TetriminoShape)shape);
  }
  if (IsKeyPressed(KEY_Z)) { this->tetrimino.rotate(Rotate::CCW); }
  if (IsKeyPressed(KEY_X)) { this->tetrimino.rotate(Rotate::CW); }

  if (IsKeyPressed(KEY_W)) { this->tetriminoMove(Direction::Up); }
  if (IsKeyPressed(KEY_S)) { this->tetriminoMove(Direction::Down); }
  if (IsKeyPressed(KEY_A)) { this->tetriminoMove(Direction::Left); }
  if (IsKeyPressed(KEY_D)) { this->tetriminoMove(Direction::Right); }

  if (IsKeyPressed(KEY_SPACE)) { this->tetriminoPlaced(); }

  tetrimino.draw(x, y, mino_size);

  for (auto [row, col, mino] : *this) {
    if (mino) {
      DrawRectangleV(
          this->tetrimino.calculateMinoPosition(x, y, col, row, mino_size),
              CLITERAL(Vector2){mino_size, mino_size}, MINO_DATA(mino).color);
    }
  }
}

void Maytrix::tetriminoMove(Direction dt) {
  this->tetrimino.move(dt);
  this->mino_moved.push(dt);
  if (this->tetriminoIsCollided()) {
    this->tetrimino.move(directionInverse(dt));
    if (!this->mino_moved.empty()) {
      this->mino_moved.pop();
    }
  }
}

bool Maytrix::tetriminoIsCollided() {
  int x = this->tetrimino.column;
  int y = this->tetrimino.row;
  for (auto [row, col, mino] : this->tetrimino) {
    if (mino && this->isOccupied(y + row, x + col)) {
      return true;
    }
  }
  return false;
}

bool Maytrix::isOccupied(int row, int col) {
  if (row < 0 || col < 0 || row >= this->buffer_area.size() || col >= this->buffer_area.size()) {
    return true;
  }
  return this->buffer_area[row][col];
}

bool Maytrix::tetriminoPlaced() {
  if (this->tetriminoIsCollided()) {
    return false;
  }
  int x = this->tetrimino.column;
  int y = this->tetrimino.row;
  for (auto [row, col, mino] : this->tetrimino) {
    if (mino) {
      this->buffer_area[y+row][x+col] = (int)this->tetrimino.shape;
    }
  }
  return true;
}

void Maytrix::tetriminoReset() {
  this->tetrimino.reset();
  std::stack<Direction> empty;
  this->mino_moved.swap(empty);
}

BufferAreaIterator Maytrix::begin() {
  return BufferAreaIterator(&this->buffer_area);
}

BufferAreaIterator Maytrix::end() {
  return BufferAreaIterator(&this->buffer_area, this->buffer_area.size());
}
