//
// Created by Kamil Prorok on 26.01.2025.
//

#ifndef GUI_H
#define GUI_H

namespace ui {


class UI {
public:
  static void show_project_name();
  static void show_decks_title();
  static void show_no_decks();
  static void get_file_path(char* path, int* length);
};

} // gui

#endif //GUI_H
