//
// Created by Kamil Prorok on 26.01.2025.
//

#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <vector>
#include <unordered_map>
#include <string>

#include "data/Deck.h"
#include "models/Deck.h"

namespace db {
  class Database {
  private:
    sqlite3 *db;
    const char *DB_NAME = "flashcards.db";

    void execute_sql(const char *sql);
    void execute_sql(const char *sql, std::vector<std::unordered_map<std::string, std::string>>& results);
    void create_tables();

  public:
    Database();
    ~Database();

    bool is_connected() const;
    void get_decks(std::vector<models::Deck>& decks);
    void get_cards(int deck_id, std::vector<data::Question>& questions);
    void insert_deck(const data::Deck& deck);
  };
} // db

#endif //DATABASE_H
