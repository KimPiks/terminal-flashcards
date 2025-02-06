//
// Created by Kamil Prorok on 01.02.2025.
//

#include "Files.h"

#include <conio.h>
#include <fstream>
#include <cstring>
#include <string>
#include <regex>
#include <filesystem>

#include "Utils.h"

namespace files {
  void Files::validate_file(const std::string &path) {
    // Check if file exists
    std::ifstream file;
    file.open(path);

    if (!file.good()) {
      throw std::invalid_argument("File not found.");
    }

    // Check if file is formatted correctly
    std::string line;
    std::getline(file, line);

    // Check if the first line (set name) is not empty
    if (line.empty()) {
      throw std::invalid_argument("File format error: The first line (set name) cannot be empty.");
    }

    const std::regex question_regex("^#.*$");
    const std::regex answer_regex("^[+-].*$");

    bool expect_question = true;

    while (std::getline(file, line)) {
        if (expect_question) {
            // Validate question format
            if (!std::regex_match(line, question_regex)) {
                throw std::invalid_argument("File format error: Expected a question line starting with '#'.");
            }
            expect_question = false;
        } else {
            // Validate answer format
            if (!std::regex_match(line, answer_regex)) {
                throw std::invalid_argument("File format error: Expected an answer line starting with '+' or '-'.");
            }

            // Ensure there's at least one correct answer
            bool has_correct_answer = false;
            do {
                if (line[0] == '+') {
                    if (has_correct_answer) {
                        throw std::invalid_argument("File format error: Multiple correct answers for one question.");
                    }
                    has_correct_answer = true;
                }
            } while (std::getline(file, line) && std::regex_match(line, answer_regex));

            if (!has_correct_answer) {
                throw std::invalid_argument("File format error: No correct answer provided for a question.");
            }

            expect_question = true;

            // If the loop breaks on a non-answer line, re-check the line
            if (!file.eof()) {
                file.seekg(-line.size() - 1, std::ios_base::cur);
            }
        }
    }

    if (!expect_question) {
        throw std::invalid_argument("File format error: Missing answers for the last question.");
    }
  }

  void Files::load_deck(const std::string &path, data::Deck* deck) {
    try {
      validate_file(path);
    } catch (const std::invalid_argument &e) {
      ui::Utils::color(ui::Utils::Color::RED);
      printf("\n==== ERROR ====\n");
      printf("%s\n", e.what());
      printf("===============\n");

      getch();
      exit(1);
    }

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