#include <iostream>
#include <algorithm>
#include <functional>
#include "tetris_matrix.hpp"
#include "rotation.hpp"

Maytrix::Maytrix() {
  // this->buffer_area = BufferArea(44, std::vector<int>(10));
  this->buffer_area = {
    {0,1,1,2,3,4,4,5,5,6},
    {0,1,2,2,3,4,5,5,6,6},
    {0,0,0,2,3,4,0,0,6,3},
    {0,0,0,0,3,0,0,0,0,3},
    {0,0,0,0,0,0,0,0,0,3},
    {0,0,0,0,0,0,0,0,0,3},
  };
  while (this->buffer_area.size() < 44) {
    this->buffer_area.push_back(std::vector<int>(10));
  }
}

void Maytrix::update() {

}

void Maytrix::removeClearedLines() {
  int last_line = 0;
  for (int i = 0; i < this->buffer_area.size(); i++) {
    bool isfull = false;
    for (auto mino : this->buffer_area[i]) {
      isfull = mino > 0;
      if (!isfull) { break; }
    }

    if (isfull) {
      for (auto &mino : this->buffer_area[i]) { mino = 0; }
    } else {
      if (i != last_line) {
        for (int j = 0; j < this->buffer_area[0].size(); j++) {
          this->buffer_area[last_line][j] = this->buffer_area[i][j];
        }
      }
      last_line++;
    }
  }
}

int Maytrix::moveToSurface() {
  int move_count = -1;
  while (!this->tetriminoIsCollided()) {
    this->tetrimino.move(Direction::Down);
    move_count++;
  }
  if (move_count >= 0) {
    this->tetrimino.move(Direction::Up);
  }
  return std::max(move_count, 0);
}

void Maytrix::moveToRow(int count) {
  this->tetrimino.move(Direction::Up, count);
  if (this->tetriminoIsCollided()) {
    throw std::runtime_error("Maytrix::moveToRow - Tetrimino is collided!");
  }
}

bool Maytrix::tetriminoIsCollided() {
  for (auto [row, col, mino] : this->tetrimino) {
    if (mino && this->isMinoOccupied(this->tetrimino.row + row, this->tetrimino.column + col)) {
      return true;
    }
  }
  return false;
}

bool Maytrix::isMinoOccupied(int row, int col) {
  if (row < 0 || col < 0 || row >= this->buffer_area.size() || col >= this->buffer_area.size()) {
    return true;
  }
  return this->buffer_area[row][col];
}

void Maytrix::tetriminoPlace(TetriminoShape next) {
  for (auto [row, col, mino] : this->tetrimino) {
    if (mino) {
      this->buffer_area[this->tetrimino.row+row][this->tetrimino.column+col]
        = (int)this->tetrimino.shape;
    }
  }
  this->tetrimino.swap(next);
}

void Maytrix::restart() {
  for (auto &line : this->buffer_area) {
    for (auto &mino : line) {
      mino = 0;
    }
  }
}

bool Maytrix::tetriminoRotate(Rotate rt) {
  this->tetrimino.rotate(rt);
  if (this->tetriminoIsCollided()) {
    this->tetrimino.rotate(rotateInverse(rt));
    return false;
  }
  return true;
}

bool Maytrix::tetriminoMove(Direction dt) {
  if (this->tetriminoTryMove(dt)) {
    this->tetrimino.move(dt);
    return true;
  }
  return false;
}

bool Maytrix::tetriminoTryMove(Direction dt) {
  this->tetrimino.move(dt);
  bool can_move = !this->tetriminoIsCollided();
  this->tetrimino.move(directionInverse(dt));
  return can_move;
}

bool Maytrix::tetriminoTryRotate(Rotate rt) {
  this->tetrimino.rotate(rt);
  bool can_rotate = !this->tetriminoIsCollided();
  this->tetrimino.rotate(rotateInverse(rt));
  return can_rotate;
}

BufferAreaIterator Maytrix::begin() {
  return BufferAreaIterator(&this->buffer_area);
}

BufferAreaIterator Maytrix::end() {
  return BufferAreaIterator(&this->buffer_area, this->buffer_area.size());
}
