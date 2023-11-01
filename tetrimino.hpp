#pragma once

#include <vector>
#include <raylib.h>
#include <tuple>
#include <array>
#include "matrix_ds.hpp"
#include "axis.hpp"
#include "rotation.hpp"

enum struct TetriminoShape {
  None, O, I, T, L, J, S, Z, Last,
};

#define LIGHTBLUE (CLITERAL(Color){ 173, 216, 230, 255 })

struct __MinoData {
  TetriminoShape type;
  Color color;
  BufferArea data;
  int row, column;
};

inline std::array<__MinoData, (int)TetriminoShape::Last> __mino_data = {
  CLITERAL(__MinoData)({TetriminoShape::None, CLITERAL(Color){0,0,0,0}, {}, 0, 0}),
  CLITERAL(__MinoData)({
      TetriminoShape::O, YELLOW,
      {
        {1, 1},
        {1, 1},
      }, 20, 4,
    }),
  CLITERAL(__MinoData)({
      TetriminoShape::I, LIGHTBLUE,
      {
        {0,0,0,0},
        {1,1,1,1},
        {0,0,0,0},
        {0,0,0,0},
      }, 19, 3,
    }),
  CLITERAL(__MinoData)({
      TetriminoShape::T, PURPLE,
      {
        {0,0,0},
        {1,1,1},
        {0,1,0},
      }, 19, 3,
    }),
  CLITERAL(__MinoData)({
      TetriminoShape::L, ORANGE,
      {
        {0,0,0},
        {1,1,1},
        {1,0,0},
      }, 19, 3,
    }),
  CLITERAL(__MinoData)({
      TetriminoShape::J, DARKBLUE,
      {
        {0,0,0},
        {1,1,1},
        {0,0,1},
      }, 19, 3,
    }),
  CLITERAL(__MinoData)({
      TetriminoShape::S, GREEN,
      {
        {0,0,0},
        {0,1,1},
        {1,1,0},
      }, 19, 3,
    }),
  CLITERAL(__MinoData)({
      TetriminoShape::Z, RED,
      {
        {0,0,0},
        {1,1,0},
        {0,1,1},
      }, 19, 3,
    }),
};

#define MINO_DATA(T) (__mino_data[(int)T])

// tm = tetrimino
struct Tetrimino {
  Tetrimino() = default;
  Tetrimino(TetriminoShape type);

  void move(Axis dt, int count);
  void rotate(Rotate rotate);
  void flip(Axis flip);
  void swap(TetriminoShape type);
  int at(int col, int row);
  int length();
  BufferAreaIterator begin();
  BufferAreaIterator end();

  int column, row;
  Color color;
  TetriminoShape shape;
  BufferArea data;
};
