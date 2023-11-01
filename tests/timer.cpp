#include <bits/chrono.h>
#include <iostream>
#include <raylib.h>
#include <string>
#include "../time.hpp"

using namespace std;

int main() {
  Time::Timer timer;
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
    } else if (IsKeyPressed(KEY_S)) {
      timer.start();
    } else if (IsKeyPressed(KEY_T)) {
      timer.toggle();
    } else if (IsKeyPressed(KEY_D)) {
      timer.addTime(-10s);
    } else if (IsKeyPressed(KEY_A)) {
      timer.addTime(10s);
    }
    BeginDrawing();
    ClearBackground(BLACK);
    DrawText(("Micro : " + to_string(timer.asMicro().count())).c_str(), 0, 0, 16, WHITE);
    DrawText(("Milli : " + to_string(timer.asMilli().count())).c_str(), 0, 17, 16, WHITE);
    DrawText(("Secs  : " + to_string(timer.asSecs().count())).c_str(), 0, 33, 16, WHITE);
    auto dur = std::chrono::duration<float>(timer.asMicro());
    DrawText(("Dec   : " + to_string(dur.count())).c_str(), 0, 49, 16, WHITE);
    Time::us us = std::chrono::duration_cast<Time::us>(dur);
    DrawText(("Micro : " + to_string(us.count())).c_str(), 0, 65, 16, WHITE);
    EndDrawing();
  }
  CloseWindow();
  return 0;
}
