//
// Created by MG on 20/12/2025.
//

#ifndef WISIELEC_CATEGORIES_LOGIC_H
#define WISIELEC_CATEGORIES_LOGIC_H

#include <vector>
#include <string>
#include "models.h"
#include <fstream>

enum class Category {
    Animals,
    Electronics,
    Fruits,
    SchoolSubjects,
    Mix
};

std::string categoryToString(Category cat);

std::string categoryToFileName(Category cat);

void loadWordsFromFile(const std::string &fileName, std::vector<std::string> &words);

std::vector<std::string> loadCategory(Category cat);

#endif //WISIELEC_CATEGORIES_LOGIC_H