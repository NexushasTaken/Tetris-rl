#include "mino_shape.hpp"

std::array<MinoShapeData, MinoShape_Last> MinoShape::mino_data = {
  CLITERAL(MinoShapeData)({MinoShape_None, CLITERAL(Color){0,0,0,0}, {}, 0, 0}),
  CLITERAL(MinoShapeData)({
      MinoShape_O, YELLOW,
      {
        {1, 1},
        {1, 1},
      }, 20, 4,
    }),
  CLITERAL(MinoShapeData)({
      MinoShape_I, LIGHTBLUE,
      {
        {0,0,0,0},
        {1,1,1,1},
        {0,0,0,0},
        {0,0,0,0},
      }, 19, 3,
    }),
  CLITERAL(MinoShapeData)({
      MinoShape_T, PURPLE,
      {
        {0,0,0},
        {1,1,1},
        {0,1,0},
      }, 19, 3,
    }),
  CLITERAL(MinoShapeData)({
      MinoShape_L, ORANGE,
      {
        {0,0,0},
        {1,1,1},
        {1,0,0},
      }, 19, 3,
    }),
  CLITERAL(MinoShapeData)({
      MinoShape_J, DARKBLUE,
      {
        {0,0,0},
        {1,1,1},
        {0,0,1},
      }, 19, 3,
    }),
  CLITERAL(MinoShapeData)({
      MinoShape_S, GREEN,
      {
        {0,0,0},
        {0,1,1},
        {1,1,0},
      }, 19, 3,
    }),
  CLITERAL(MinoShapeData)({
      MinoShape_Z, RED,
      {
        {0,0,0},
        {1,1,0},
        {0,1,1},
      }, 19, 3,
    }),
};
