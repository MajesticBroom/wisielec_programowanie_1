//
// Created by MG on 20/12/2025.
//

#include "categories_logic.h"

#include <iostream>

std::string categoryToString(const Category cat) {
    switch (cat) {
        case Category::Animals:
            return "Zwierzęta";
        case Category::Electronics:
            return "Elektronika";
        case Category::Fruits:
            return "Owoce";
        case Category::SchoolSubjects:
            return "Przedmioty szkolne";
        default:
            return "Mieszane";
    }
}


std::string categoryToFileName(const Category cat) {
    switch (cat) {
        case Category::Animals:             return "animals.txt";
        case Category::Electronics:         return "electronics.txt";
        case Category::Fruits:              return "fruits.txt";
        case Category::SchoolSubjects:      return "schoolSubjects.txt";
        default:                            return ""; // traktujemy jak Mix
    }
}

void loadWordsFromFile(const std::string &fileName, std::vector<std::string> &words) {
    std::ifstream file(fileName);

    if (!file.is_open()) {
        // logowanie błędu
        std::cout << "Błąd pobierania pliku" << std::endl;
        return;
    }

    std::string word;
    while (std::getline(file, word)) {
        if (!word.empty()) {
            words.push_back(word);
        }
    }
    file.close();
}


std::vector<std::string> loadCategory(const Category cat) {
    std::vector<std::string> words;

    // CLION musi być ustawiony tak,
    // że working directory to katalog zawierający wszystkie pliki .cpp,
    // a nie katalog build
    const std::string path = "words/";

    if (cat == Category::Mix || cat < Category::Animals || cat > Category::SchoolSubjects) {
        // dla Mix wczytujemy wszystkie kategorie

        const std::vector<Category> allCategories = {
            Category::Animals,
            Category::Electronics,
            Category::Fruits,
            Category::SchoolSubjects
        };

        for (const Category c : allCategories) {
            std::string fileName = path + categoryToFileName(c);
            loadWordsFromFile(fileName, words);
        }
    } else {
        // dla konkretnej kategorii wczytujemy tylko jeden plik
        const std::string fileName = path + categoryToFileName(cat);
        loadWordsFromFile(fileName, words);
    }

    return words;
}
