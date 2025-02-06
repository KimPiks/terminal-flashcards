//
// Created by Kamil Prorok on 01.02.2025.
//

#ifndef FLASHCARDS_H
#define FLASHCARDS_H
#include "Database.h"

namespace fc {

/**
 * Class that represents the flashcards main logic.
 */
class Flashcards {
private:
  /**
   * Database instance.
   */
  db::Database db;

  /**
   * Shows the main menu options.
   */
  void show_main_menu_options();

  /**
   * Shows decks menu.
   */
  void show_decks();

  /**
   * Shows the import deck menu.
   */
  void import_deck();

  /**
   * Runs the flashcards.
   * @param deck Deck to run flashcards.
   */
  void run_flashcards(data::Deck& deck);

public:
  /**
   * Constructor.
   * @param db Database instance.
   */
  Flashcards(const db::Database& db) : db(db) {}

  /**
   * Shows the main menu of application.
   */
  void show_main_menu();
};

} // FC

#endif //FLASHCARDS_H
