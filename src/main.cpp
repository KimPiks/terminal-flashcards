#include <cstdio>
#include <sqlite3.h>

#include "UI.h"
#include "database/Database.h"
#include "flashcards/Flashcards.h"

int main() {
  db::Database db;
  if (!db.is_connected()) {
    printf("Flashcards database is not connected!\n");
    return 1;
  }

  fc::Flashcards flashcards(db);
  flashcards.show_main_menu();

  while (true) {}

  return 0;
}
