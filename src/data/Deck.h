//
// Created by Kamil Prorok on 01.02.2025.
//

#ifndef DECK_H
#define DECK_H
#include <vector>

#include "Question.h"

namespace data {
  struct Deck {
    char name[256];
    std::vector<Question> questions;
  };
}

#endif //DECK_H
