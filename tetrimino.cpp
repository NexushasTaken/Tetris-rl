#include <raylib.h>
#include <utility>
#include <cstdio>
#include <cmath>
#include "tetrimino.hpp"
#include "matrix_ds.hpp"
#include "direction.hpp"
#include "rotation.hpp"

Tetrimino::Tetrimino(TetriminoShape shape) {
  this->swap(shape);
}

void Tetrimino::move(Direction dt) {
  if ((int)dt < 0 || (int)dt >= (int)Direction::Last)
    return;
  switch (dt) {
    case Direction::Up:
      this->row++;
      break;
    case Direction::Down:
      this->row--;
      break;
    case Direction::Left:
      this->column--;
      break;
    case Direction::Right:
      this->column++;
      break;
    default:
      break;
  }
}

void Tetrimino::swap(TetriminoShape shape) {
  auto &mino_data = MINO_DATA(shape);
  this->column = mino_data.column;
  this->row = mino_data.row;
  this->shape = shape;
  this->color = mino_data.color;
  auto &data = mino_data.data;
  this->data = std::vector(data.begin(), data.end());
}

void Tetrimino::reset() {
  this->swap(this->shape);
  this->column = 0;
  this->row = 0;
}

void Tetrimino::flip(Flip flip) {
  int i, j, half, length;

  length = this->data.size();
  half = (int)std::floor(length/2.0);
  for (i = 0; i < half; i++) {
    for (j = 0; j < length; j++) {
      if (flip == Flip::X) {
        std::swap(this->data[j][i], this->data[j][length-i-1]);
      } else {
        std::swap(this->data[i][j], this->data[length-i-1][j]);
      }
    }
  }
}

void Tetrimino::rotate(Rotate rotate) {
  std::vector<std::vector<int>> old_data(this->data.begin(), this->data.end());
  int i, j, length;

  length = data.size();

  for (i = 0; i < length; i++) {
    for (j = 0; j < length; j++) {
      if (rotate == Rotate::CW) {
        this->data[j][i] = old_data[length-i-1][length-j-1];
      } else {
        this->data[j][i] = old_data[i][j];
      }
    }
  }
  this->flip(Flip::Y);
}

BufferAreaIterator Tetrimino::begin() {
  return BufferAreaIterator(&this->data);
}

BufferAreaIterator Tetrimino::end() {
  return BufferAreaIterator(&this->data, this->data.size());
}
