//
// Created by Kamil Prorok on 31.01.2025.
//

#include "Select.h"
#include "Utils.h"

#include <cstdio>

namespace ui {
  int Select::show_select_menu(const std::vector<std::string> &options, const int x, const int y, const int space) {
    int selected = 0;
    int key = 0;
    while (key != 13) {
      Utils::color();

      for (int i = 0; i < options.size(); i++) {
        Utils::clear_line(y + i * space); // Clear previous option before printing new one
        Utils::gotoxy(x, y + i * space);

        if (i == selected) {
          Utils::color(Utils::GRAY);
        } else {
          Utils::color();
        }

        printf("%s", options[i].c_str());
      }

      // Change selected option
      key = Utils::get_key();
      if (key == 80 && selected < options.size() - 1) {
        selected++;
      } else if (key == 72 && selected > 0) {
        selected--;
      }
    }
    return selected;
  }

} // ui