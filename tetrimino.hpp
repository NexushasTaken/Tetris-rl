#pragma once

#include <vector>
#include <raylib.h>
#include <tuple>
#include <array>
#include "matrix_ds.hpp"

enum struct TetriminoShape {
  O, I, T, L, J, S, Z, Last,
};

#define LIGHTBLUE (CLITERAL(Color){ 173, 216, 230, 255 })

struct __MinoData {
  TetriminoShape type;
  Color color;
  MatrixDS data;
};

inline std::array<__MinoData, 8> __mino_data = {
  CLITERAL(__MinoData)({
      TetriminoShape::O, YELLOW,
      {
        {1, 1},
        {1, 1},
      },
    }),
  CLITERAL(__MinoData)({
      TetriminoShape::I, LIGHTBLUE,
      {
        {0,0,0,0},
        {0,0,0,0},
        {1,1,1,1},
        {0,0,0,0},
      },
    }),
  CLITERAL(__MinoData)({
      TetriminoShape::T, PURPLE,
      {
        {0,1,0},
        {1,1,1},
        {0,0,0},
      },
    }),
  CLITERAL(__MinoData)({
      TetriminoShape::L, ORANGE,
      {
        {0,0,1},
        {1,1,1},
        {0,0,0},
      },
    }),
  CLITERAL(__MinoData)({
      TetriminoShape::J, DARKBLUE,
      {
        {1,0,0},
        {1,1,1},
        {0,0,0},
      },
    }),
  CLITERAL(__MinoData)({
      TetriminoShape::S, GREEN,
      {
        {0,1,1},
        {1,1,0},
        {0,0,0},
      },
    }),
  CLITERAL(__MinoData)({
      TetriminoShape::Z, RED,
      {
        {1,1,0},
        {0,1,1},
        {0,0,0},
      },
    }),
  CLITERAL(__MinoData)({TetriminoShape::Last, WHITE, {}}),
};

#define MINO_DATA(T) (__mino_data[(int)T])

enum struct Direction {
  Up, Down, Left, Right, Last,
};

enum struct Rotate {
  ClockWise,
  CounterClockWise,
  CW, // ClockWise
  CCW, // CounterClockWise
  Last,
};

enum struct Flip {
  X, Y, Last,
};

struct Tetrimino {
  Tetrimino(TetriminoShape type);

  void draw(int offx, int offy, float size);
  void rotate(Rotate rotate);
  void flip(Flip flip);
  void swap(TetriminoShape type);
  void reset();
  MatrixDSIterator begin();
  MatrixDSIterator end();

  int column, row;
  Color color;
  TetriminoShape shape;
  MatrixDS data;
};
