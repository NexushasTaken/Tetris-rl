#include <raylib.h>
#include <utility>
#include <cmath>
#include "tetrimino.hpp"
#include "matrix_ds.hpp"

void Tetrimino::draw(int offx, int offy, float size) {
  for (auto [row, col, mino] : *this) {
    if (mino) {
      DrawRectangle(
          col * size + offx,
          row * size + offy,
          size, size,
          this->color);
    }    
  }
}

Tetrimino::Tetrimino(TetriminoShape shape) {
  this->column = 0;
  this->row = 0;
  this->swap(shape);
}

void Tetrimino::swap(TetriminoShape shape) {
  this->shape = shape;
  this->color = MINO_DATA(shape).color;
  auto &data = MINO_DATA(shape).data;
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

MatrixDSIterator Tetrimino::begin() {
  return MatrixDSIterator(&this->data);
}

MatrixDSIterator Tetrimino::end() {
  return MatrixDSIterator(&this->data, this->data.size());
}
