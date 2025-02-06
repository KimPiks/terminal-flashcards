//
// Created by Kamil Prorok on 01.02.2025.
//

#include "Files.h"

#include <fstream>
#include <cstring>
#include <string>

namespace files {
  void Files::load_deck(const std::string &path, data::Deck* deck) {
    std::ifstream file;
    file.open(path);

    // deck name
    std::string name;
    std::getline(file, name);
    strcpy(deck->name, name.c_str());

    while (!file.eof()) {
      std::string line;
      std::getline(file, line);

      if (line[0] == '#') {
        // question
        data::Question question;
        strcpy(question.question, line.c_str() + 1);

        // answers
        while (!file.eof() && file.peek() != '#') {
          std::string answer;
          std::getline(file, answer);

          data::Answer a{};
          if (answer[0] == '+') {
            a.is_correct = true;
            strcpy(a.answer, answer.c_str() + 1);
          } else {
            a.is_correct = false;
            strcpy(a.answer, answer.c_str() + 1);
          }

          question.answers.push_back(a);
        }

        deck->questions.push_back(question);
      }
    }
  }

} // files