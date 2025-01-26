#include <cstdio>
#include <sqlite3.h>

#include "UI.h"
#include "database/Database.h"

int main() {
  db::Database db;
  ui::UI::show_main_menu();

  while (true) {}
  return 0;
}
