//
// Created by Kamil Prorok on 01.02.2025.
//

#ifndef FILES_H
#define FILES_H
#include "data/Deck.h"

namespace files {

class Files {
public:
  static void load_deck(const char* path, data::Deck* deck);
};

} // files

#endif //FILES_H
