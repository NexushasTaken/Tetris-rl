#pragma once

#include <vector>

using MatrixDS = std::vector<std::vector<int>>;

struct MatrixDSIterator {
  MatrixDS *matrix;
  int row;
  int col;
  MatrixDSIterator(MatrixDS *matrix);
  MatrixDSIterator(MatrixDS *matrix, int row);
  bool is_end();
  std::tuple<int, int, int> operator*();
  virtual MatrixDSIterator& operator++();
  bool operator!=(MatrixDSIterator &other);
};
