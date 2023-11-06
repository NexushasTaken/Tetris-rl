#pragma once
#include <raylib.h>
#include <stdexcept>
#include <array>
#include <string>
#include "matrix_ds.hpp"

enum _MinoShape {
  MinoShape_None,
  MinoShape_O,
  MinoShape_I,
  MinoShape_T,
  MinoShape_L,
  MinoShape_J,
  MinoShape_S,
  MinoShape_Z,
  MinoShape_Last,
};

#define LIGHTBLUE (CLITERAL(Color){ 173, 216, 230, 255 })

struct MinoShapeData {
  int shape;
  Color color;
  BufferArea data;
  int row, column;
};

struct MinoShape {
  inline int operator()() { return this->shape; }
  inline bool operator==(int shape) {
    return this->shape == shape;
  }
  inline int operator=(int shape) {
    this->shape = shape;
    return this->shape;
  }

  static auto& at(int shape) {
    if (shape < MinoShape_None || shape >= MinoShape_Last) {
      throw std::runtime_error("invalid shape: " + std::to_string(shape));
    }
    return MinoShape::mino_data[shape];
  }

  inline const BufferArea &getData() { return MinoShape::at(this->shape).data; }
  inline Color &getColor() { return MinoShape::at(this->shape).color; }
  inline std::tuple<int, int> getLocation(int width=0, int height=0)  {
    auto &data = MinoShape::mino_data[this->shape];
    return std::make_tuple(data.row, data.column);
  }

private:
  int shape;
  static std::array<MinoShapeData, MinoShape_Last> mino_data;
}; 
