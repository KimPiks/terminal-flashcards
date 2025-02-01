//
// Created by Kamil Prorok on 01.02.2025.
//

#ifndef FLASHCARDS_H
#define FLASHCARDS_H
#include "Database.h"

namespace fc {

class Flashcards {
private:
  db::Database db;

  void show_main_menu_options();
  void show_decks();
  void import_deck();

public:
  Flashcards(const db::Database& db) : db(db) {}
  void show_main_menu();
};

} // FC

#endif //FLASHCARDS_H
