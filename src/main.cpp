#include <cstdio>
#include <windows.h>
#include "database/Database.h"
#include "flashcards/Flashcards.h"

int main() {
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);

  db::Database db;
  if (!db.is_connected()) {
    printf("Flashcards database is not connected!\n");
    return 1;
  }

  fc::Flashcards flashcards(db);
  flashcards.show_main_menu();

  return 0;
}
