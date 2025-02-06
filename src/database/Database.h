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
  /**
   * Class that represents database connection.
   */
  class Database {
  private:
    /**
     * Database instance.
     */
    sqlite3 *db;

    /**
     * Name of the database file.
     */
    const char *DB_NAME = "flashcards.db";

    /**
     * Execute SQL query.
     * @param sql SQL query.
     */
    void execute_sql(const char *sql) const;

    /**
     * Execute SQL query and get results.
     * @param sql SQL query.
     * @param results Results.
     */
    void execute_sql(const char *sql, std::vector<std::unordered_map<std::string, std::string>>& results) const;

    /**
     * Create tables in the database.
     */
    void create_tables() const;

  public:
    /**
     * Constructor.
     */
    Database();

    /**
     * Destructor.
     */
    ~Database();

    /**
     * Check if the database is connected.
     * @return True if connected, false otherwise.
     */
    bool is_connected() const;

    /**
     * Get all decks.
     * @param decks Decks.
     */
    void get_decks(std::vector<models::Deck>& decks) const;

    /**
     * Get questions from the deck.
     * @param deck_id Deck id.
     * @param questions Questions.
     */
    void get_cards(int deck_id, std::vector<data::Question>& questions) const;

    /**
     * Insert deck into the database.
     * @param deck Deck.
     */
    void insert_deck(const data::Deck& deck) const;
  };
} // db

#endif //DATABASE_H
