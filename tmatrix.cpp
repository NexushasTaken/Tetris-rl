#include <iostream>
#include <algorithm>
#include <functional>
#include "tmatrix.hpp"
#include "rotation.hpp"
#include "axis.hpp"

TMatrix::TMatrix() {
  this->field_vec = MatrixVec(44, std::vector<int>(10));
}

void TMatrix::removeClearedLines() {
  int last_line = 0;
  for (std::vector<int> &line : this->field_vec) {
    bool isfull =
      std::find_if(
          line.begin(), line.end(),
          [](auto mino) { return mino == 0; }) == line.end();

    if (isfull) {
      std::fill(line.begin(), line.end(), 0);
    } else {
      if (this->field_vec[last_line].begin() != line.begin()) {
        std::copy(line.begin(), line.end(), this->field_vec[last_line].begin());
      }
      last_line++;
    }
  }
}

int TMatrix::moveToSurface() {
  int move_count = -1;
  while (!this->tetriminoIsCollided()) {
    this->piece.move(Axis::Y, -1);
    move_count++;
  }
  if (move_count >= 0) {
    this->piece.move(Axis::Y, 1);
  }
  return std::max(move_count, 0);
}

void TMatrix::moveToRow(int count) {
  this->piece.move(Axis::Y, count);
  if (this->tetriminoIsCollided()) {
    throw std::runtime_error("Maytrix::moveToRow - Tetrimino is collided!");
  }
}

bool TMatrix::tetriminoIsCollided() {
  for (auto [row, col, mino] : this->piece) {
    if (mino && this->isMinoOccupied(this->piece.row + row, this->piece.column + col)) {
      return true;
    }
  }
  return false;
}

bool TMatrix::isMinoOccupied(int row, int col) {
  if (row < 0 || col < 0 || row >= this->rowLength() || col >= this->columnLength()) {
    return true;
  }
  return this->field_vec[row][col];
}

void TMatrix::tetriminoPlace(TMinoShape next) {
  for (auto [row, col, mino] : this->piece) {
    if (mino) {
      this->field_vec[this->piece.row+row][this->piece.column+col]
        = (int)this->piece.shape;
    }
  }
  this->piece.swap(next);
}

void TMatrix::restart() {
  for (auto &line : this->field_vec) {
    std::fill(line.begin(), line.end(), 0);
  }
}

bool TMatrix::tetriminoRotate(Rotate rt) {
  this->piece.rotate(rt);
  if (this->tetriminoIsCollided()) {
    this->piece.rotate(rotateInverse(rt));
    return false;
  }
  return true;
}

bool TMatrix::tetriminoMove(Axis dt, int count) {
  if (this->tetriminoCanMove(dt, count)) {
    this->piece.move(dt, count);
    return true;
  }
  return false;
}

bool TMatrix::tetriminoIsOnSurface() {
  return !this->tetriminoCanMove(Axis::Y, -1);
}

bool TMatrix::tetriminoCanMove(Axis dt, int count) {
  this->piece.move(dt, count);
  bool can_move = !this->tetriminoIsCollided();
  this->piece.move(dt, -count);
  return can_move;
}

bool TMatrix::tetriminoCanRotate(Rotate rt) {
  this->piece.rotate(rt);
  bool can_rotate = !this->tetriminoIsCollided();
  this->piece.rotate(rotateInverse(rt));
  return can_rotate;
}

int TMatrix::rowLength() {
  return this->field_vec.size();
}
int TMatrix::columnLength() {
  return this->field_vec.at(0).size();
}

Matrix2DIterator TMatrix::begin() {
  return Matrix2DIterator(&this->field_vec);
}

Matrix2DIterator TMatrix::end() {
  return Matrix2DIterator(&this->field_vec, this->field_vec.size());
}
