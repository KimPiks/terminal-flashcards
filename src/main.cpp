#include <cstdio>
#include "database/Database.h"
#include "flashcards/Flashcards.h"

#ifdef _WIN32
#include <windows.h>
#endif

int main() {
#ifdef _WIN32
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);
#endif

  db::Database db;
  if (!db.is_connected()) {
    printf("Flashcards database is not connected!\n");
    return 1;
  }

  fc::Flashcards flashcards(db);
  flashcards.show_main_menu();

  return 0;
}
