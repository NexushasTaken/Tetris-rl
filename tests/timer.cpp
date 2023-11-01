#include <bits/chrono.h>
#include <iostream>
#include <raylib.h>
#include <string>
#include "../time.hpp"

using namespace std;

int main() {
  Time::Timer timer;
  Time::IncrementalTimer inc_timer;
  InitWindow(400, 400, "EventTimer");
  while (!WindowShouldClose()) {
    if (IsKeyPressed(KEY_P)) {
      timer.pause();
    } else if (IsKeyPressed(KEY_U)) {
      timer.unpause();
    } else if (IsKeyPressed(KEY_E)) {
      timer.restart();
    } else if (IsKeyPressed(KEY_R)) {
      timer.reset();
      inc_timer.reset();
    } else if (IsKeyPressed(KEY_S)) {
      timer.start();
      inc_timer.start(500ms);
    } else if (IsKeyPressed(KEY_T)) {
      timer.toggle();
    } else if (IsKeyPressed(KEY_D)) {
      timer.addTime(-10s);
    } else if (IsKeyPressed(KEY_A)) {
      timer.addTime(10s);
    }
    BeginDrawing();
    ClearBackground(BLACK);

    int y = -17;
    int size = 16;
    auto next = [&y, size]() {
      y += size + 1;
      return y;
    };
    DrawText(("Micro : "s + to_string(timer.asMicro().count())).c_str(), 0, next(), size, WHITE);
    DrawText(("Milli : "s + to_string(timer.asMilli().count())).c_str(), 0, next(), size, WHITE);
    DrawText(("Secs  : "s + to_string(timer.asSecs().count())).c_str(), 0, next(), size, WHITE);
    auto dur = std::chrono::duration<float>(timer.asMicro());
    DrawText(("Dec   : "s + to_string(dur.count())).c_str(), 0, next(), size, WHITE);
    Time::us us = std::chrono::duration_cast<Time::us>(dur);
    DrawText(("Micro : "s + to_string(us.count())).c_str(), 0, next(), size, WHITE);
    next();
    DrawText(("IsElapsed : "s + (inc_timer.isElapsed() ? "True" : "False")).c_str(), 0, next(), size, WHITE);
    DrawText(("time(us): "s + std::to_string(inc_timer.asMicro().count())).c_str(), 0, next(), size, WHITE);
    inc_timer.isElapsed(true);
    EndDrawing();
  }
  CloseWindow();
  return 0;
}
