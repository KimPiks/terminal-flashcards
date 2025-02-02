//
// Created by Kamil Prorok on 01.02.2025.
//

#include "Flashcards.h"

#include <algorithm>
#include <conio.h>
#include <cstdlib>
#include <cstring>
#include <random>

#include "Database.h"
#include "Select.h"
#include "UI.h"
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
    char* options[] = {"Show decks", "Import deck", "Quit"};
    int selected = ui::Select::show_select_menu(options, 3, 50, 12, 2, ui::Utils::PURPLE);

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

    std::vector<db::models::Deck> decks;
    db.get_decks(decks);

    if (decks.empty()) {
      ui::UI::show_no_decks();
      return;
    }

    char* deck_names[decks.size()];
    for (size_t i = 0; i < decks.size(); i++) {
      deck_names[i] = decks[i].name;
    }

    int selected = ui::Select::show_select_menu(deck_names, decks.size(), 50, 8, 2, ui::Utils::PURPLE);
    std::vector<data::Question> cards;
    db.get_cards(decks[selected].deck_id, cards);

    data::Deck deck;
    strcpy(deck.name, decks[selected].name);
    deck.questions = cards;

    run_flashcards(deck);
  }

  void Flashcards::import_deck() {
    ui::Utils::clear();

    char filePath[256];
    int length;
    ui::UI::get_file_path(filePath, &length);
    data::Deck deck;
    files::Files::load_deck(filePath, &deck);

    db.insert_deck(deck);

    show_decks();
  }

  void Flashcards::run_flashcards(data::Deck &deck) {
    std::shuffle(deck.questions.begin(), deck.questions.end(), std::mt19937(std::random_device()()));
    int correct_answers_count = 0;

    int question_number = 1;
    for (const auto& card : deck.questions) {
      ui::Utils::clear();
      ui::UI::show_question(card.question);
      ui::UI::show_question_number(question_number++, deck.questions.size());

      char* answers[card.answers.size()];
      for (size_t i = 0; i < card.answers.size(); i++) {
        answers[i] = strdup(card.answers[i].answer);
      }

      int x = 50;
      int y = 8;
      int space = 2;
      int selected = ui::Select::show_select_menu(answers, card.answers.size(), x, y, space, ui::Utils::PURPLE);
      if (card.answers[selected].is_correct) {
        ui::Utils::gotoxy(x, y + selected * space);
        ui::Utils::color(ui::Utils::GREEN);
        printf("✓ %s", card.answers[selected].answer);
        correct_answers_count++;
      } else {
        ui::Utils::gotoxy(x, y + selected * space);
        ui::Utils::color(ui::Utils::RED);
        printf("✗ %s", card.answers[selected].answer);

        for (int i = 0; i < card.answers.size(); i++) {
          if (card.answers[i].is_correct) {
            ui::Utils::gotoxy(x, y + i * space);
            ui::Utils::color(ui::Utils::GREEN);
            printf("✓ %s", card.answers[i].answer);
          }
        }
      }

      getch();
    }

    ui::UI::show_points(correct_answers_count, deck.questions.size());
  }


} // FC