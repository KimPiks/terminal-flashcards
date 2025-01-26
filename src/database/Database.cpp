//
// Created by Kamil Prorok on 26.01.2025.
//

#include "Database.h"

#include <cstdio>

namespace db {
  Database::Database() {
    if (sqlite3_open(DB_NAME, &db) != SQLITE_OK) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return;
    }

    this->create_tables();
  }

  Database::~Database() {
    if (sqlite3_close(db) != SQLITE_OK) {
      fprintf(stderr, "Can't close database: %s\n", sqlite3_errmsg(db));
    }
  }

  void Database::execute_sql(const char *sql) {
    char *err_msg = nullptr;
    if (sqlite3_exec(db, sql, nullptr, nullptr, &err_msg) != SQLITE_OK) {
      fprintf(stderr, "SQL error: %s\n", err_msg);
      sqlite3_free(err_msg);
    }
  }


  void Database::create_tables() {
    this->execute_sql(CREATE_DECKS_TABLE_SQL);
    this->execute_sql(CREATE_CARDS_TABLE_SQL);
    this->execute_sql(CREATE_ANSWERS_TABLE_SQL);
    this->execute_sql(CREATE_PROGRESS_TABLE_SQL);
  }

} // db