#pragma once

#include <vector>

using MatrixVec = std::vector<std::vector<int>>;

struct Matrix2DIterator {
  MatrixVec *matrix;
  int row;
  int col;
  Matrix2DIterator(MatrixVec *matrix);
  Matrix2DIterator(MatrixVec *matrix, int row);
  bool isEnd();
  std::tuple<int, int, int> operator*();
  virtual Matrix2DIterator& operator++();
  bool operator!=(Matrix2DIterator &other);
};
