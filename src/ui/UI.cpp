//
// Created by Kamil Prorok on 26.01.2025.
//

#include "UI.h"

#include <cstdio>
#include <iostream>

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
    std::getline(std::cin, *path);
  }

  void UI::show_question(const std::string &question) {
    Utils::color(Utils::Color::WHITE);
    printf("%s", question.c_str());
  }

  void UI::show_number_of_correct_answers(const int correct, const int total, const int incorrect) {
    Utils::color(Utils::Color::GRAY);
    printf("Correct: ");
    Utils::color(Utils::Color::GREEN);
    printf("%d", correct);
    Utils::color(Utils::Color::GRAY);
    printf(" | Incorrect: ");
    Utils::color(Utils::Color::RED);
    printf("%d", incorrect);
    Utils::color(Utils::Color::GRAY);
    printf(" | Left: ");
    Utils::color(Utils::Color::WHITE);
    printf("%d", total - correct);
  }

  void UI::show_deck_summary(const int correct, const int total, const int repeated) {
    Utils::color(Utils::Color::WHITE);
    printf("You answered %d out of %d questions correctly!\n", correct, total);
    printf("Repeated questions: %d\n\n", repeated);
    printf("Press any key to continue...");
  }

} // GUI