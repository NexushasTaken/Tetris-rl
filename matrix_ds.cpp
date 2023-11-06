#include "matrix_ds.hpp"

Matrix2DIterator::Matrix2DIterator(MatrixVec *matrix)
  : matrix(matrix), row(0), col(0) {}
Matrix2DIterator::Matrix2DIterator(MatrixVec *matrix, int row)
  : matrix(matrix), row(row), col(row) {}

bool Matrix2DIterator::isEnd() {
  return this->row == this->matrix->size();
}

bool Matrix2DIterator::operator!=(Matrix2DIterator &other) {
  return !this->isEnd();
} 

Matrix2DIterator& Matrix2DIterator::operator++() {
  if (this->isEnd()) {
    return *this;
  }

  this->col++;
  if (this->col >= this->matrix->at(0).size()) {
    this->col = 0;
    this->row++;
  }
  return *this;
}

std::tuple<int, int, int> Matrix2DIterator::operator*() {
  return std::make_tuple(row, col, (*this->matrix)[row][col]);
}
