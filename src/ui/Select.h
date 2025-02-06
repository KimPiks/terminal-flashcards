//
// Created by Kamil Prorok on 31.01.2025.
//

#ifndef SELECT_H
#define SELECT_H
#include <string>
#include <vector>

namespace ui {

/**
  * Class that provides a method to show a select menu.
*/
class Select {
public:
  /**
    * Shows a select menu with given options.
    * @param options - vector of strings with options to choose from.
    * @param x - x position of the menu.
    * @param y - y position of the menu.
    * @param space - space between options.
    * @return index of the selected option.
  */
  static int show_select_menu(const std::vector<std::string> &options, int x, int y, int space);
};

} // ui

#endif //SELECT_H
