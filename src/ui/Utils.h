//
// Created by Kamil Prorok on 26.01.2025.
//

#ifndef UTILS_H
#define UTILS_H

namespace ui {

class Utils {
public:
  enum Color {
    RED = 31,
    GREEN = 32,
    BLUE = 34,
    YELLOW = 33,
    WHITE = 37,
    GRAY = 90,
    PURPLE = 35,
    ORANGE = 91
  };

  static void gotoxy(int x, int y);
  static void color(Color color);
  static void color();
  static void clear();
  static int get_key();
  static void clear_line(int y);
};

} // ui

#endif //UTILS_H
