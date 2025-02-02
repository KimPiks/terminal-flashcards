//
// Created by Kamil Prorok on 26.01.2025.
//

#include "UI.h"

#include <cstdio>
#include <cstdlib>
#include <string.h>

#include "Select.h"
#include "Utils.h"

namespace ui {
  void UI::show_project_name() {
    Utils::gotoxy(20, 3);
    printf("  _                 _           _      __ _         _                   _    \n");
    Utils::gotoxy(20, 4);
    printf(" | |_ ___ _ _ _ __ (_)_ _  __ _| |___ / _| |__ _ __| |_  __ __ _ _ _ __| |___\n");
    Utils::gotoxy(20, 5);
    printf(" |  _/ -_) '_| '  \\| | ' \\/ _` | |___|  _| / _` (_-< ' \\/ _/ _` | '_/ _` (_-<\n");
    Utils::gotoxy(20, 6);
    printf("  \\__\\___|_| |_|_|_|_|_||_\\__,_|_|   |_| |_\\__,_/__/_||_\\__\\__,_|_| \\__,_/__/\n\n");
  }

  void UI::show_decks_title() {
    Utils::gotoxy(50, 3);
    Utils::color(Utils::Color::YELLOW);
    printf("~ Available decks ~");
  }

  void UI::show_no_decks() {
    Utils::gotoxy(50, 5);
    Utils::color(Utils::Color::RED);
    printf("No decks available!");
  }

  void UI::get_file_path(char *path, int *length) {
    Utils::color(Utils::Color::WHITE);
    printf("Input flashcards file path: ");
    scanf("%s", path);
    *length = static_cast<int>(strlen(path));
  }

  void UI::show_question(const char *question) {
    Utils::color(Utils::Color::WHITE);
    Utils::gotoxy(50, 5);
    printf("%s", question);
  }

  void UI::show_question_number(const int number, const int total) {
    Utils::gotoxy(1, 1);
    Utils::color(Utils::Color::GRAY);
    printf("%d/%d", number, total);
  }

  void UI::show_points(const int correct, const int total) {
    Utils::clear();
    Utils::gotoxy(50, 5);
    Utils::color(Utils::Color::WHITE);
    printf("You answered %d out of %d questions correctly!", correct, total);
  }

} // GUI