//
// Created by Kamil Prorok on 26.01.2025.
//

#include "UI.h"

#include <cstdio>

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

  void UI::show_main_menu_options() {
    Utils::color(Utils::PURPLE);
    Utils::gotoxy(50, 12);
    printf("1. Show decks");
    Utils::gotoxy(50, 14);
    printf("2. Import deck");
    Utils::gotoxy(50, 16);
    printf("3. Quit");
  }

  void UI::show_main_menu() {
    Utils::clear();
    show_project_name();
    show_main_menu_options();
  }
} // GUI