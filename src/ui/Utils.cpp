//
// Created by Kamil Prorok on 26.01.2025.
//

#include "Utils.h"

#include <cstdio>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

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
#ifdef _WIN32
    return _getch();
#else
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
#endif
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