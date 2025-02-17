﻿//
// Created by Kamil Prorok on 26.01.2025.
//

#include "Database.h"

#include <cstdio>

#include "Sql.h"
#include "data/Deck.h"

namespace db {
  Database::Database() {
    if (sqlite3_open(DB_NAME, &db) != SQLITE_OK) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return;
    }

    this->create_tables();
  }

  Database::~Database() {
    if (!is_connected()) return;
    
    if (sqlite3_close(db) != SQLITE_OK) {
      fprintf(stderr, "Can't close database: %s\n", sqlite3_errmsg(db));
    }
  }

  bool Database::is_connected() const {
    return db != nullptr;
  }

  void Database::execute_sql(const char *sql) const {
    if (!is_connected()) {
      fprintf(stderr, "Database is not connected!\n");
      return;
    }

    char *err_msg = nullptr;
    if (sqlite3_exec(db, sql, nullptr, nullptr, &err_msg) != SQLITE_OK) {
      fprintf(stderr, "SQL error: %s\n", err_msg);
      sqlite3_free(err_msg);
    }
  }

  void Database::execute_sql(const char *sql, std::vector<std::unordered_map<std::string, std::string>>& results) const {
    if (!is_connected()) {
      fprintf(stderr, "Database is not connected!\n");
      return;
    }

    sqlite3_stmt* stmt = nullptr;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
      fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
      return;
    }

    const int columnCount = sqlite3_column_count(stmt);
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
      std::unordered_map<std::string, std::string> row;
      for (int i = 0; i < columnCount; ++i) {
        const char* columnName = sqlite3_column_name(stmt, i);
        const char* columnValue = reinterpret_cast<const char*>(sqlite3_column_text(stmt, i));
        row[columnName] = columnValue ? columnValue : "";
      }
      results.push_back(std::move(row));
    }

    if (rc != SQLITE_DONE) {
      fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
      sqlite3_finalize(stmt);
      return;
    }

    sqlite3_finalize(stmt);
  }

  void Database::create_tables() const {
    this->execute_sql(CREATE_DECKS_TABLE_SQL);
    this->execute_sql(CREATE_CARDS_TABLE_SQL);
    this->execute_sql(CREATE_ANSWERS_TABLE_SQL);
  }

  void Database::get_decks(std::vector<models::Deck>& decks) const {
    std::vector<std::unordered_map<std::string, std::string>> results;

    this->execute_sql(SELECT_ALL_DECKS_SQL, results);

    for (const auto& row : results) {
      models::Deck deck{};
      for (const auto& [key, value] : row) {
        if (key == "deck_id") {
          deck.deck_id = std::stoi(value);
        } else if (key == "name") {
          snprintf(deck.name, sizeof(deck.name), "%s", value.c_str());
        }
      }
      decks.push_back(deck);
    }
  }

  void Database::insert_deck(const data::Deck &deck) const {
    execute_sql(BEGIN_TRANSACTION_SQL);

    char insertDeckSql[256];
    snprintf(insertDeckSql, sizeof(insertDeckSql), INSERT_DECK_SQL, deck.name);
    execute_sql(insertDeckSql);

    std::vector<std::unordered_map<std::string, std::string>> results;
    execute_sql(SELECT_LAST_INSERTED_DECK_ID_SQL, results);
    const int deckId = std::stoi(results[0].begin()->second);

    // questions
    for (const auto &[question, answers] : deck.questions) {
      char insertCardSql[256];
      snprintf(insertCardSql, sizeof(insertCardSql), INSERT_CARD_SQL, deckId, question);
      execute_sql(insertCardSql);

      results.clear();
      execute_sql(SELECT_LAST_INSERTED_DECK_ID_SQL, results);
      const int cardId = std::stoi(results[0].begin()->second);

      // answers
      for (const auto &[answer, is_correct] : answers) {
        char insertAnswerSql[256];
        snprintf(insertAnswerSql, sizeof(insertAnswerSql), INSERT_ANSWER_SQL, cardId, answer, is_correct);
        execute_sql(insertAnswerSql);
      }
    }

    execute_sql(COMMIT_SQL);
  }

  void Database::get_cards(const int deck_id, std::vector<data::Question> &questions) const {
    char selectCardsByDeckIdSql[256];
    snprintf(selectCardsByDeckIdSql, sizeof(selectCardsByDeckIdSql), SELECT_CARDS_BY_DECK_ID_SQL, deck_id);
    std::vector<std::unordered_map<std::string, std::string>> results;
    execute_sql(selectCardsByDeckIdSql, results);

    for (const auto& row : results) {
      data::Question question{};
      for (const auto& [key, value] : row) {
        if (key == "question") {
          snprintf(question.question, sizeof(question.question), "%s", value.c_str());
        }

        if (key == "card_id") {
          int cardId = std::stoi(value);
          char selectAnswersByCardIdSql[256];
          snprintf(selectAnswersByCardIdSql, sizeof(selectAnswersByCardIdSql), SELECT_ANSWERS_BY_CARD_ID_SQL, cardId);
          std::vector<std::unordered_map<std::string, std::string>> answersResults;
          execute_sql(selectAnswersByCardIdSql, answersResults);

          for (const auto& answerRow : answersResults) {
            data::Answer answer{};
            for (const auto& [answerKey, answerValue] : answerRow) {
              if (answerKey == "answer") {
                snprintf(answer.answer, sizeof(answer.answer), "%s", answerValue.c_str());
              }

              if (answerKey == "is_correct") {
                answer.is_correct = answerValue == "1";
              }
            }
            question.answers.push_back(answer);
          }
        }
      }
      questions.push_back(question);
    }
  }


} // db