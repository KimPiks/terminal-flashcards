//
// Created by Kamil Prorok on 26.01.2025.
//

#include "Utils.h"

#include <cstdio>
#include <conio.h>

namespace ui {
  void Utils::gotoxy(const int x, const int y) {
    printf("\x1B[%d;%df", y, x);
    fflush(stdout);
  }

  void Utils::color(const Color color) {
    printf("\x1B[%dm", color);
    fflush(stdout);
  }

  void Utils::color() {
    color(Color::WHITE);
  }

  void Utils::clear() {
    printf("\x1B[2J\x1B[H");
    fflush(stdout);
  }

  int Utils::get_key() {
    return _getch();
  }

  void Utils::clear_line(int y) {
    gotoxy(0, y);
    printf("\x1B[2K");
    fflush(stdout);
  }

  char Utils::get_answer_letter(const int index) {
    return 'a' + index;
  }


} // ui