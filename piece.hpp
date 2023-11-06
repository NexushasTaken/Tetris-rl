#pragma once

#include <vector>
#include <raylib.h>
#include <tuple>
#include <array>
#include "matrix_ds.hpp"
#include "axis.hpp"
#include "rotation.hpp"

using TMinoShape = int;
enum _TMinoShape {
  TMinoShape_None,
  TMinoShape_O,
  TMinoShape_I,
  TMinoShape_T,
  TMinoShape_L,
  TMinoShape_J,
  TMinoShape_S,
  TMinoShape_Z,
  TMinoShape_Last
};

#define LIGHTBLUE (CLITERAL(Color){ 173, 216, 230, 255 })

struct __MinoData {
  int type;
  Color color;
  MatrixVec data;
  int row, column;
};

inline std::array<__MinoData, TMinoShape_Last> __mino_data = {
  CLITERAL(__MinoData)({TMinoShape_None, CLITERAL(Color){0,0,0,0}, {}, 0, 0}),
  CLITERAL(__MinoData)({
      TMinoShape_O, YELLOW,
      {
        {1, 1},
        {1, 1},
      }, 20, 4,
    }),
  CLITERAL(__MinoData)({
      TMinoShape_I, LIGHTBLUE,
      {
        {0,0,0,0},
        {1,1,1,1},
        {0,0,0,0},
        {0,0,0,0},
      }, 19, 3,
    }),
  CLITERAL(__MinoData)({
      TMinoShape_T, PURPLE,
      {
        {0,0,0},
        {1,1,1},
        {0,1,0},
      }, 19, 3,
    }),
  CLITERAL(__MinoData)({
      TMinoShape_L, ORANGE,
      {
        {0,0,0},
        {1,1,1},
        {1,0,0},
      }, 19, 3,
    }),
  CLITERAL(__MinoData)({
      TMinoShape_J, DARKBLUE,
      {
        {0,0,0},
        {1,1,1},
        {0,0,1},
      }, 19, 3,
    }),
  CLITERAL(__MinoData)({
      TMinoShape_S, GREEN,
      {
        {0,0,0},
        {0,1,1},
        {1,1,0},
      }, 19, 3,
    }),
  CLITERAL(__MinoData)({
      TMinoShape_Z, RED,
      {
        {0,0,0},
        {1,1,0},
        {0,1,1},
      }, 19, 3,
    }),
};

#define MINO_DATA(T) (__mino_data[(int)T])

struct Piece {
  void move(Axis dt, int count);
  void rotate(Rotate rotate);
  void flip(Axis flip);
  void swap(TMinoShape type);
  int at(int col, int row);
  int length();
  Matrix2DIterator begin();
  Matrix2DIterator end();

  int column, row;
  Color color;
  TMinoShape shape;
  MatrixVec data;
};
