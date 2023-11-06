#pragma once

#include <vector>
#include <stack>
#include "time.hpp"
#include "piece.hpp"
#include "axis.hpp"
#include "rotation.hpp"

// Tetris Matrix
struct TMatrix {
  TMatrix();
  bool tetriminoIsCollided();
  void tetriminoPlace(TMinoShape next);
  void removeClearedLines();
  bool isMinoOccupied(int row, int col);
  // Return move count
  int moveToSurface();
  void moveToRow(int count);
  void restart();

  bool tetriminoIsOnSurface();
  bool tetriminoMove(Axis dt, int count);
  bool tetriminoRotate(Rotate rt);
  bool tetriminoCanMove(Axis dt, int count);
  bool tetriminoCanRotate(Rotate rt);

  int rowLength();
  int columnLength();

  Matrix2DIterator begin();
  Matrix2DIterator end();

  Piece piece;
  MatrixVec field_vec;
};
