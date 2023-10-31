#include <iostream>
#include <algorithm>
#include "tetris_matrix.hpp"
#include "rotation.hpp"

Maytrix::Maytrix() : tetrimino(TetriminoShape::O) {
  this->tetrimino.swap(TetriminoShape::O);
  // this->buffer_area = BufferArea(40, std::vector<int>(10));
  this->buffer_area = {
    {1,1,1,2,3,4,4,5,5,6},
    {0,1,2,2,3,4,5,5,6,6},
    {0,0,0,2,3,4,0,0,6,3},
    {0,0,0,0,3,0,0,0,0,3},
    {0,0,0,0,0,0,0,0,0,3},
    {0,0,0,0,0,0,0,0,0,3},
  };
  while (this->buffer_area.size() < 40) {
    this->buffer_area.push_back(std::vector<int>(10));
  }
}

void Maytrix::tetriminoRotate(Rotate rt) {
  this->tetrimino.rotate(rt);
  this->mino_rotate.push(rt);
  if (this->tetriminoIsCollided()) {
    this->tetrimino.rotate(rotateInverse(rt));
    if (!this->mino_rotate.empty()) {
      this->mino_rotate.pop();
    }
  }
}

void Maytrix::tetriminoMove(Direction dt) {
  this->tetrimino.move(dt);
  this->mino_moved.push(dt);
  if (this->tetriminoIsCollided()) {
    this->tetrimino.move(directionInverse(dt));
    if (!this->mino_moved.empty()) {
      this->mino_moved.pop();
    }
  }
}

int Maytrix::drop() {
  int move_count = -1;
  while (!this->tetriminoIsCollided()) {
    this->tetrimino.move(Direction::Down);
    move_count++;
  }
  this->tetrimino.move(Direction::Up);
  return std::max(move_count, 0);
}

void Maytrix::undrop(int count) {
  this->tetrimino.move(Direction::Up, count);
}

bool Maytrix::tetriminoIsCollided() {
  int x = this->tetrimino.column;
  int y = this->tetrimino.row;
  for (auto [row, col, mino] : this->tetrimino) {
    if (mino && this->isOccupied(y + row, x + col)) {
      return true;
    }
  }
  return false;
}

bool Maytrix::isOccupied(int row, int col) {
  if (row < 0 || col < 0 || row >= this->buffer_area.size() || col >= this->buffer_area.size()) {
    return true;
  }
  return this->buffer_area[row][col];
}

// TODO: Hard Drop must not be instant
bool Maytrix::hardDrop(TetriminoShape next) {
  if (this->tetriminoIsCollided()) {
    return false;
  }
  this->drop();
  int x = this->tetrimino.column;
  int y = this->tetrimino.row;
  for (auto [row, col, mino] : this->tetrimino) {
    if (mino) {
      this->buffer_area[y+row][x+col] = (int)this->tetrimino.shape;
    }
  }
  this->tetriminoSwap(next);
  return true;
}

void Maytrix::tetriminoSwap(TetriminoShape shape) {
  this->tetrimino.swap(shape);
}

void Maytrix::tetriminoReset() {
  this->tetriminoSwap(this->tetrimino.shape);
  std::stack<Direction> empty;
  this->mino_moved.swap(empty);
}

BufferAreaIterator Maytrix::begin() {
  return BufferAreaIterator(&this->buffer_area);
}

BufferAreaIterator Maytrix::end() {
  return BufferAreaIterator(&this->buffer_area, this->buffer_area.size());
}
