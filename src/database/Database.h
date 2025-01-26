//
// Created by Kamil Prorok on 26.01.2025.
//

#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>

namespace db {
  class Database {
  private:
    sqlite3 *db;
    const char *DB_NAME = "flashcards.db";

    const char *CREATE_DECKS_TABLE_SQL = "CREATE TABLE IF NOT EXISTS decks ("
                                     "deck_id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                     "name VARCHAR(64) NOT NULL,"
                                     "created_at DATETIME DEFAULT CURRENT_TIMESTAMP"
                                     ");";

    const char *CREATE_CARDS_TABLE_SQL = "CREATE TABLE IF NOT EXISTS cards ("
                                     "card_id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                     "deck_id INTEGER NOT NULL,"
                                     "question VARCHAR(256) NOT NULL,"
                                     "created_at DATETIME DEFAULT CURRENT_TIMESTAMP,"
                                     "FOREIGN KEY (deck_id) REFERENCES decks(id)"
                                     ");";

    const char *CREATE_ANSWERS_TABLE_SQL = "CREATE TABLE IF NOT EXISTS card_answers ("
                                           "answer_id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                           "card_id INTEGER NOT NULL,"
                                           "answer VARCHAR(256) NOT NULL,"
                                           "created_at DATETIME DEFAULT CURRENT_TIMESTAMP,"
                                           "is_correct BOOLEAN NOT NULL,"
                                           "FOREIGN KEY (card_id) REFERENCES cards(id)"
                                           ");";

    const char *CREATE_PROGRESS_TABLE_SQL = "CREATE TABLE IF NOT EXISTS progress ("
                                            "progress_id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                            "card_id INTEGER NOT NULL,"
                                            "deferred_until DATETIME,"
                                            "is_mastered BOOLEAN NOT NULL,"
                                            "created_at DATETIME DEFAULT CURRENT_TIMESTAMP,"
                                            "FOREIGN KEY (card_id) REFERENCES cards(id)"
                                            ");";

    void execute_sql(const char *sql);
    void create_tables();

  public:
    Database();
    ~Database();
  };
} // db

#endif //DATABASE_H
