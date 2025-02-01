//
// Created by Kamil Prorok on 01.02.2025.
//

#ifndef QUESTION_H
#define QUESTION_H
#include "Answer.h"

namespace data {
  struct Question {
    char question[256];
    std::vector<Answer> answers;
  };
}

#endif //QUESTION_H
