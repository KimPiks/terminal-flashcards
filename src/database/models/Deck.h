//
// Created by Kamil Prorok on 01.02.2025.
//

#ifndef DB_DECK_H
#define DB_DECK_H


namespace db::models {

struct Deck {
  int deck_id;
  char name[64];
};

} // models
// db

#endif //DB_DECK_H
