#ifndef WISIELEC_MODELS_H
#define WISIELEC_MODELS_H

#include <string>
#include <vector>
// #include <optional>
#include <unordered_set>

struct Keyword {
    std::string word;
    int length;

    // Keyword(std::string w = "") {
    //     word = w;
    //     length = w.length();
    // }
};

struct Player {
    std::string nickname;
    std::unordered_set<char> usedLetters;
    int correctlyGuessedLetters;
    int livesLeft;
    int points;
    int matchesPlayed;
    int matchesWon;
    int totalPoints;
};


struct PlayerStats {
    int matchesPlayed = 0;
    int matchesWon = 0;
    int totalPoints = 0;
    bool found = false;
};

#endif //WISIELEC_MODELS_H