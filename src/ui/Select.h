//
// Created by Kamil Prorok on 31.01.2025.
//

#ifndef SELECT_H
#define SELECT_H
#include "Utils.h"

namespace ui {

class Select {
public:
  static int show_select_menu(char* options[], int size, int x, int y, int space, Utils::Color color);
};

} // ui

#endif //SELECT_H
