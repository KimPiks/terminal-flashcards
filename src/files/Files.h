//
// Created by Kamil Prorok on 01.02.2025.
//

#ifndef FILES_H
#define FILES_H
#include <string>

#include "data/Deck.h"

namespace files {

/**
 * Class responsible for loading and saving files.
 */
class Files {
private:
  /**
   * Validates file format.
   * @param path Path to the file.
   */
  static void validate_file(const std::string &path);

public:
  /**
   * Load deck from file.
   * @param path Path to the file.
   * @param deck Deck to load.
   */
  static void load_deck(const std::string &path, data::Deck* deck);
};

} // files

#endif //FILES_H
