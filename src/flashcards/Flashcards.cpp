//
// Created by Kamil Prorok on 01.02.2025.
//

#include "Flashcards.h"

#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <random>

#include "Database.h"
#include "Select.h"
#include "UI.h"
#include "Utils.h"
#include "files/Files.h"
#include "models/Deck.h"

namespace db::models {
  struct Deck;
}

namespace modelss {
  struct Decks;
}

namespace fc {
  void Flashcards::show_main_menu_options() {
    const std::vector<std::string> options = {"Show decks", "Import deck", "Quit"};
    const int selected = ui::Select::show_select_menu(options, 0, 3, 1);

    switch (selected) {
      case 0:
        show_decks();
        break;
      case 1:
        import_deck();
        break;
      case 2:
        default:
          exit(0);
    }
  }

  void Flashcards::show_main_menu() {
    ui::Utils::clear();
    ui::UI::show_project_name();
    show_main_menu_options();
  }

  void Flashcards::show_decks() {
    ui::Utils::clear();
    ui::UI::show_decks_title();

    // Get all decks from database
    std::vector<db::models::Deck> decks;
    db.get_decks(decks);

    // If there are no decks, show message and return
    if (decks.empty()) {
      ui::UI::show_no_decks();
      return;
    }

    // Copy deck names to vector
    std::vector<std::string> deck_names(decks.size());
    for (size_t i = 0; i < decks.size(); i++) {
      deck_names[i] = decks[i].name;
    }

    // Show select menu
    const int selected = ui::Select::show_select_menu(deck_names, 0, 3, 1);

    // Get cards from selected deck
    std::vector<data::Question> cards;
    db.get_cards(decks[selected].deck_id, cards);

    // Create deck
    data::Deck deck;
    strcpy(deck.name, decks[selected].name);
    deck.questions = cards;

    // Run flashcards
    run_flashcards(deck);
  }

  void Flashcards::import_deck() {
    ui::Utils::clear();

    // Get file path from user
    std::string file_path;
    ui::UI::get_file_path(&file_path);

    // Load deck from file
    data::Deck deck;
    files::Files::load_deck(file_path, &deck);

    // Insert deck to database
    db.insert_deck(deck);

    show_decks();
  }

  void Flashcards::run_flashcards(data::Deck &deck) {
    // Shuffle questions
    std::ranges::shuffle(deck.questions, std::mt19937(std::random_device()()));
    const int deck_size = deck.questions.size();

    std::vector<data::Question> repeated_questions;
    int max_repeated_questions = 0;

    int correct_answers_count = 0;
    int correct_first_attempt_answers_count = 0;
    while (!deck.questions.empty() || !repeated_questions.empty()) {
      data::Question card = deck.questions.front();
      bool repeated = false;
      if (deck.questions.empty()) {
        if (repeated_questions.size() > max_repeated_questions) {
          max_repeated_questions = repeated_questions.size();
        }

        card = repeated_questions.front();
        repeated = true;
      }

      // Show question
      ui::Utils::clear();
      ui::UI::show_number_of_correct_answers(correct_answers_count, deck_size, repeated_questions.size());
      printf("\n\n");
      ui::UI::show_question(card.question);

      // Copy answers to vector
      std::vector<std::string> answers(card.answers.size());
      for (size_t i = 0; i < card.answers.size(); i++) {
        answers[i] = ui::Utils::get_answer_letter(i) + std::string(") ") + strdup(card.answers[i].answer);
      }

      const int x = 0;
      const int y = 5;
      const int space = 1;
      const int selected = ui::Select::show_select_menu(answers, x, y, space);

      ui::Utils::clear_line(y + selected * space);
      ui::Utils::gotoxy(x, y + selected * space);

      if (card.answers[selected].is_correct) {
        // Show correct answer
        ui::Utils::color(ui::Utils::GREEN);
        printf("✓ %s", card.answers[selected].answer);

        if (!repeated) {
          correct_first_attempt_answers_count++;
        }
        correct_answers_count++;
      } else {
        // Show incorrect answer
        ui::Utils::color(ui::Utils::RED);
        printf("✗ %s", card.answers[selected].answer);

        // Show correct answer
        for (int i = 0; i < card.answers.size(); i++) {
          if (card.answers[i].is_correct) {
            ui::Utils::gotoxy(x, y + i * space);
            ui::Utils::color(ui::Utils::GREEN);
            ui::Utils::clear_line(y + i * space);
            printf("✓ %s", card.answers[i].answer);
          }
        }

        // Add incorrect answered question to the end of the deck
        repeated_questions.push_back(card);
      }
      if (repeated) {
        repeated_questions.erase(repeated_questions.begin());
      } else {
        deck.questions.erase(deck.questions.begin());
      }

      // Wait for any key to continue
      ui::Utils::get_key();
    }

    // Show summary
    ui::Utils::clear();
    ui::Utils::gotoxy(0, 0);
    ui::UI::show_deck_summary(correct_first_attempt_answers_count, deck_size, max_repeated_questions);

    // Wait for any key to continue
    ui::Utils::get_key();
    show_main_menu();
  }


} // FC