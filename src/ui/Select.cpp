//
// Created by Kamil Prorok on 31.01.2025.
//

#include "Select.h"

#include <cstdio>

namespace ui {
  int Select::show_select_menu(char* options[], int size, int x, int y, int space, Utils::Color color) {
    int selected = 0;
    int key = 0;
    while (key != 13) {
      Utils::color(color);
      for (int i = 0; i < size; i++) {
        Utils::clear_line(y + i * space);
        Utils::gotoxy(x, y + i * space);
        if (i == selected) {
          Utils::color(Utils::BLUE);
          printf("> %s", options[i]);
        } else {
          Utils::color(color);
          printf("%s", options[i]);
        }
      }
      key = Utils::get_key();
      if (key == 80 && selected < size - 1) {
        selected++;
      } else if (key == 72 && selected > 0) {
        selected--;
      }
    }
    return selected;
  }

} // ui