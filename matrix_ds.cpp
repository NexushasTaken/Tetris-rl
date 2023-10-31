#include "matrix_ds.hpp"

BufferAreaIterator::BufferAreaIterator(BufferArea *matrix)
  : matrix(matrix), row(0), col(0) {}
BufferAreaIterator::BufferAreaIterator(BufferArea *matrix, int row)
  : matrix(matrix), row(row), col(row) {}

bool BufferAreaIterator::isEnd() {
  return this->row == this->matrix->size();
}

bool BufferAreaIterator::operator!=(BufferAreaIterator &other) {
  return !this->isEnd();
} 

BufferAreaIterator& BufferAreaIterator::operator++() {
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

std::tuple<int, int, int> BufferAreaIterator::operator*() {
  return std::make_tuple(row, col, (*this->matrix)[row][col]);
}
