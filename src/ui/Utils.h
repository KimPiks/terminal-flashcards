//
// Created by Kamil Prorok on 26.01.2025.
//

#ifndef UTILS_H
#define UTILS_H

namespace ui {

/**
 * Utils class contains static methods that are used for user interface purposes.
 */
class Utils {
public:
  /**
   * List of colors that can be used in the console.
   */
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

  /**
   * Moves the cursor to the specified position.
   * @param x - x coordinate
   * @param y - y coordinate
   */
  static void gotoxy(int x, int y);

  /**
   * Changes the color of the text in the console.
   * @param color - color to be set
   */
  static void color(Color color);

  /**
   * Sets the default color of the text in the console.
   */
  static void color();

  /**
   * Clears the console.
   */
  static void clear();

  /**
   * Gets the key from the console.
   * @return - key code
   */
  static int get_key();

  /**
   * Clears the line in the console.
   * @param y - y coordinate of the line
   */
  static void clear_line(int y);

  /**
   * Gets the letter of the answer based on the index.
   * @param index - index of the answer
   * @return - letter of the answer
   */
  static char get_answer_letter(int index);
};

} // ui

#endif //UTILS_H
