//
// Created by Kamil Prorok on 01.02.2025.
//

#ifndef SQL_H
#define SQL_H

namespace db {
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

  const char *SELECT_ALL_DECKS_SQL = "SELECT * FROM decks;";

  const char *BEGIN_TRANSACTION_SQL = "BEGIN TRANSACTION;";

  const char *COMMIT_SQL = "COMMIT;";

  const char *INSERT_DECK_SQL = "INSERT INTO decks (name) VALUES ('%s');";

  const char *SELECT_LAST_INSERTED_DECK_ID_SQL = "SELECT last_insert_rowid();";

  const char *INSERT_CARD_SQL = "INSERT INTO cards (deck_id, question) VALUES (%d, '%s');";

  const char *INSERT_ANSWER_SQL = "INSERT INTO card_answers (card_id, answer, is_correct) VALUES (%d, '%s', %d);";

}

#endif //SQL_H
