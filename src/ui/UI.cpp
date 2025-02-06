//
// Created by Kamil Prorok on 26.01.2025.
//

#include "UI.h"

#include <cstdio>
#include "Utils.h"

namespace ui {
  void UI::show_project_name() {
    Utils::color(Utils::Color::GRAY);
    printf("terminal-flashcards");
  }

  void UI::show_decks_title() {
    Utils::color(Utils::Color::YELLOW);
    printf("~ Available decks ~");
  }

  void UI::show_no_decks() {
    Utils::color(Utils::Color::RED);
    printf("No decks available!");
  }

  void UI::get_file_path(std::string* path) {
    Utils::color(Utils::Color::WHITE);
    printf("Input flashcards file path: ");
    scanf("%s", path);
  }

  void UI::show_question(const std::string &question) {
    Utils::color(Utils::Color::WHITE);
    printf("%s", question.c_str());
  }

  void UI::show_question_number(const int number, const int total) {
    Utils::color(Utils::Color::GRAY);
    printf("%d/%d", number, total);
  }

  void UI::show_points(const int correct, const int total) {
    Utils::color(Utils::Color::WHITE);
    printf("You answered %d out of %d questions correctly!", correct, total);
  }

  void UI::show_deck_summary(const int correct, const int total) {
    Utils::color(Utils::Color::WHITE);
    printf("You answered %d out of %d questions correctly!", correct, total);
  }

} // GUI