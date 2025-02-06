//
// Created by Kamil Prorok on 26.01.2025.
//

#ifndef GUI_H
#define GUI_H
#include <string>

namespace ui {

/**
 * Class that contains methods for displaying the user interface.
 */
class UI {
public:
  /**
   * Shows project name.
   */
  static void show_project_name();

  /**
   * Shows title for decks lists.
   */
  static void show_decks_title();

  /**
   * Shows message that there are no decks available.
   */
  static void show_no_decks();

  /**
   * Gets file path from user input.
   * @param path Path to file with flashcards.
   */
  static void get_file_path(std::string* path);

  /**
   * Shows question.
   * @param question Question to show.
   */
  static void show_question(const std::string &question);

  /**
   * Shows number of correct answers.
   * @param correct Number of correct answers.
   * @param total Total number of questions.
   */
  static void show_number_of_correct_answers(int correct, int total, int incorrect);

  /**
   * Shows deck summary screen.
   * @param correct Number of correct answers.
   * @param total Total number of questions.
   */
  static void show_deck_summary(int correct, int total, int repeated);
};

} // gui

#endif //GUI_H
