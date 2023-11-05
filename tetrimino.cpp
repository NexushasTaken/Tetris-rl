#include <raylib.h>
#include <stdexcept>
#include <utility>
#include <cstdio>
#include <cmath>
#include <string>
#include "tetrimino.hpp"
#include "matrix_ds.hpp"
#include "axis.hpp"
#include "rotation.hpp"

int Tetrimino::at(int col, int row) {
  return this->data[row][col];
}

int Tetrimino::length() {
  if (this->data.size() != this->data.at(0).size()) {
    throw std::runtime_error("data rows and columns lengths are not the same");
  }
  return this->data.size();
}

void Tetrimino::move(Axis dt, int count) {
  switch (dt) {
    case Axis::Y:
      this->row += count;
      break;
    case Axis::X:
      this->column += count;
      break;
    default:
      break;
  }
}

void Tetrimino::swap(TetriminoShape shape) {
  if ((int)shape < (int)TetriminoShape::None || (int)shape >= (int)TetriminoShape::Last) {
    throw std::string("invalid shape: ") + std::to_string((int)shape);
  }
  auto &mino_data = MINO_DATA(shape);
  this->column = mino_data.column;
  this->row = mino_data.row;
  this->shape = shape;
  this->color = mino_data.color;
  const auto &data = mino_data.data;
  this->data = std::vector(data.begin(), data.end());
}

void Tetrimino::flip(Axis flip) {
  int i, j, half, length;

  length = this->data.size();
  half = (int)std::floor(length/2.0);
  for (i = 0; i < half; i++) {
    for (j = 0; j < length; j++) {
      if (flip == Axis::X) {
        std::swap(this->data[j][i], this->data[j][length-i-1]);
      } else {
        std::swap(this->data[i][j], this->data[length-i-1][j]);
      }
    }
  }
}

void Tetrimino::rotate(Rotate rotate) {
  std::vector<std::vector<int>> old_data(this->data.begin(), this->data.end());
  int length = data.size();

  for (int i = 0; i < length; i++) {
    for (int j = 0; j < length; j++) {
      if (rotate == Rotate::CW) {
        this->data[j][i] = old_data[length-i-1][length-j-1];
      } else {
        this->data[j][i] = old_data[i][j];
      }
    }
  }
  this->flip(Axis::Y);
}

BufferAreaIterator Tetrimino::begin() {
  return BufferAreaIterator(&this->data);
}

BufferAreaIterator Tetrimino::end() {
  return BufferAreaIterator(&this->data, this->data.size());
}
