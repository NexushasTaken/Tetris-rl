#pragma once

#include <vector>

using BufferArea = std::vector<std::vector<int>>;

struct BufferAreaIterator {
  BufferArea *matrix;
  int row;
  int col;
  BufferAreaIterator(BufferArea *matrix);
  BufferAreaIterator(BufferArea *matrix, int row);
  bool isEnd();
  std::tuple<int, int, int> operator*();
  virtual BufferAreaIterator& operator++();
  bool operator!=(BufferAreaIterator &other);
};
