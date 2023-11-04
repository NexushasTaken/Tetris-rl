#include <iostream>
#include <raylib.h>
#include "time.hpp"
#include "tetris.hpp"

Tetris::Tetris(float mino_size, Vector2 offset) {
  this->mino_size = mino_size;
  this->offset = offset;
  this->restart();
}

void Tetris::update() {
  if (IsKeyPressed(KEY_R)) {
    this->restart();
  }
  if (game_over) {
    return;
  }

  static int shape = 1;
  if (IsKeyPressed(KEY_C)) { shape--; }
  if (IsKeyPressed(KEY_V)) { shape++; }
  if (shape >= (int)TetriminoShape::Last) { shape = 1; }
  if (shape <= 0) { shape = (int)TetriminoShape::Last-1; }

  if (IsKeyPressed(KEY_C) || IsKeyPressed(KEY_V)) {
    this->maytrix.tetrimino.swap((TetriminoShape)shape);
    this->locked_down_timer.reset();
    this->classic_drop_timer.restart();
  }
  if (IsKeyPressed(KEY_Z)) { this->maytrix.tetriminoRotate(Rotate::CW); }
  if (IsKeyPressed(KEY_X)) { this->maytrix.tetriminoRotate(Rotate::CCW); }

  if (IsKeyPressed(KEY_UP)) { this->maytrix.tetriminoMove(Axis::Y, 1); }

  if (IsKeyPressed(KEY_LEFT)) { this->maytrix.tetriminoMove(Axis::X, -1); }
  if (IsKeyPressed(KEY_RIGHT)) { this->maytrix.tetriminoMove(Axis::X, 1); }

  int down_lr = -IsKeyDown(KEY_LEFT) + IsKeyDown(KEY_RIGHT);
  if (down_lr != 0) {
    this->auto_repeat_delay_timer.update();
    this->auto_repeat_timer.update();
    this->auto_repeat_delay_timer.start(this->auto_repeat_delay_speed);
    this->auto_repeat_delay_timer.setCallback(
        [this, down_lr](auto &timer) {
          this->auto_repeat_timer.start(this->auto_repeat_speed);
          this->auto_repeat_timer.setCallback(
              [this, down_lr](auto &timer) {
                this->maytrix.tetriminoMove(Axis::X, down_lr);
              });
        });
  } else {
    auto_repeat_delay_timer.reset();
    auto_repeat_timer.reset();
  }

  this->locked_down_timer.update();

  // Drops
  bool soft_drop = IsKeyDown(KEY_DOWN);
  bool hard_drop = IsKeyPressed(KEY_SPACE);
  if (soft_drop) {
    this->soft_drop_timer.update();
    this->soft_drop_timer.start(Time::ms(this->fall_speed/this->fall_speed_multiplier));
  } else if (hard_drop) {
    startLockedDown(this->hard_locked_down_speed, true);
  } else {
    this->classic_drop_timer.update();
    startLockedDown(this->classic_locked_down_speed, false);
  }
}

void Tetris::startLockedDown(Time::us delay, bool force) {
  if (force) {
    this->maytrix.moveToSurface();
  }
  if (this->maytrix.tetriminoIsOnSurface()) {
    this->locked_down_timer.start(delay);
  }
}

void Tetris::draw() {
  float total_height = mino_size/2.0f + mino_size*20.0f;
  float total_width  = mino_size*10.0f;
  Rectangle rect = {
    .x = this->offset.x,
    .y = this->offset.y,
    .width = total_width,
    .height = total_height,
  };
  // ---- BufferBorder ----
  DrawRectangleLinesEx(rect, 1, BLACK);

  // ---- BufferVerticalLines ----
  rect.width = 2;
  for (int i = 0; i < this->maytrix.columnLength(); i++) {
    if (!i || i >= this->maytrix.rowLength()-1) {
      continue;
    }
    rect.x = i * mino_size - 1 + this->offset.x;
    DrawRectangleRec(rect, BLACK);
  }

  // ---- BufferHorizontalLines ----
  rect.x = this->offset.x;
  rect.width = total_width;
  rect.height = 2;
  for (int i = 0; i < 20; i++) {
    rect.y = i * mino_size + (mino_size/2) - 1 + this->offset.y;
    DrawRectangleRec(rect, BLACK);
  }

  // ---- BufferMinos ----
  for (auto [row, col, mino] : this->maytrix) {
    if (mino) {
      DrawRectangleV(
          this->calculateMinoPosition(this->offset.x, this->offset.y, col, row, mino_size),
              CLITERAL(Vector2){mino_size, mino_size}, MINO_DATA(mino).color);
    }
  }

  // ---- Tetrimino ----
  if (!this->game_over) {
    auto tetrimino_draw = [this]() {
      // char buffer[12];
      for (auto [row, col, mino] : this->maytrix.tetrimino) {
        Vector2 pos =
          this->calculateMinoPosition(
            this->offset.x, this->offset.y,
            col + this->maytrix.tetrimino.column, row + this->maytrix.tetrimino.row,
            mino_size);
        if (mino) {
          DrawRectangleV(pos, CLITERAL(Vector2)({mino_size, mino_size}), this->maytrix.tetrimino.color);
        }
        // sprintf(buffer, "%d:%d",
        //     col + this->maytrix.tetrimino.column,
        //     row + this->maytrix.tetrimino.row);
        // DrawText(buffer, pos.x+2, pos.y+2, 12, GRAY);
      }
    };
    tetrimino_draw();

    // ---- Ghost Tetrimino ----
    int move_count = this->maytrix.moveToSurface();
    if (move_count) {
      this->maytrix.tetrimino.color.a = 150;
      tetrimino_draw();
      this->maytrix.tetrimino.color.a = 255;
      this->maytrix.moveToRow(move_count);
    }
  }
  if (game_over) {
    DrawText("Game Over", 0, 0, 16, BLUE);
  }
}


bool Tetris::isLockedOut() {
  if (this->maytrix.tetriminoCanMove(Axis::Y, -1)) {
    return false;
  }
  int mino_ypos = 0;
  for (auto [row, col, mino] : this->maytrix.tetrimino) {
    if (mino) {
      mino_ypos = row;
      break;
    }
  }
  return this->maytrix.tetrimino.row + mino_ypos >= 20;
}


TetriminoShape Tetris::getNextShape() {
  auto next = this->bag.front();
  this->bag.pop_front();
  this->bag.push_back(this->getRandomShape());
  return next;
}

TetriminoShape Tetris::getRandomShape() {
  int rand_shape =
    this->random.randomInt(
        (int)TetriminoShape::None+1,
        (int)TetriminoShape::Last-1);
  return (TetriminoShape)rand_shape;
}


void Tetris::setGameOver() {
  this->game_over = true;
  this->resetTimers();
}

void Tetris::resetTimers() {
  this->classic_drop_timer.reset();
  this->locked_down_timer.reset();
  this->soft_drop_timer.reset();
  this->auto_repeat_timer.reset();
  this->auto_repeat_delay_timer.reset();

  this->auto_repeat_timer.setResetAfterElapsed(true);
  this->locked_down_timer.setResetAfterElapsed(true);
  this->soft_drop_timer.setResetAfterElapsed(true);

  this->locked_down_timer.setCallback(
      [this](Time::IncrementalTimer &timer) {
        if (!this->maytrix.tetriminoIsOnSurface()) {
          return;
        }
        if (this->isLockedOut()) {
          this->setGameOver();
        }
        this->maytrix.tetriminoPlace(this->getNextShape());
        if (this->maytrix.tetriminoIsCollided()) { // Block Out
          this->setGameOver();
        }
        this->maytrix.removeClearedLines();
        this->locked_down_timer.reset();
        this->classic_drop_timer.restart();
      });
  this->classic_drop_timer.setCallback(
      [this](Time::IncrementalTimer &timer){
        this->maytrix.tetriminoMove(Axis::Y, -1);
      });
  this->soft_drop_timer.setCallback(
      [this](auto &timer) {
        this->maytrix.tetriminoMove(Axis::Y, -1);
        this->startLockedDown(this->classic_locked_down_speed, false);
        if (IsKeyUp(KEY_DOWN)) {
          this->soft_drop_timer.reset();
        }
      });
}

void Tetris::restart() {
  this->game_over = false;
  this->resetTimers();
  this->fillBag();
  this->maytrix.restart();
  this->maytrix.tetrimino.swap(this->getRandomShape());
  this->holded_shape = this->getRandomShape();
  this->classic_drop_timer.start(1s);
}


void Tetris::fillBag() {
  while (this->bag.size() < 8) {
    this->bag.push_back(this->getRandomShape());
  }
}

Vector2 Tetris::calculateMinoPosition(
    float offx, float offy,
    int column, int row,
    float mino_size) {
  float x = offx;
  float y = offy;
  y += mino_size/2.0f + mino_size*20.0f;
  y -= mino_size*row + mino_size;
  x += mino_size*column;
  return CLITERAL(Vector2){x, y};
}
