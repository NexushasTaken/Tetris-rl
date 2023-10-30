#include "matrix_ds.hpp"

MatrixDSIterator::MatrixDSIterator(MatrixDS *matrix)
  : matrix(matrix), row(0), col(0) {}
MatrixDSIterator::MatrixDSIterator(MatrixDS *matrix, int row)
  : matrix(matrix), row(row), col(row) {}

bool MatrixDSIterator::is_end() {
  return this->row == this->matrix->size();
}

bool MatrixDSIterator::operator!=(MatrixDSIterator &other) {
  return !this->is_end();
} 

MatrixDSIterator& MatrixDSIterator::operator++() {
  if (this->is_end()) {
    return *this;
  }

  this->col++;
  if (this->col >= this->matrix->size()) {
    this->col = 0;
    this->row++;
  }
  return *this;
}

std::tuple<int, int, int> MatrixDSIterator::operator*() {
  return std::make_tuple(row, col, (*this->matrix)[row][col]);
}
