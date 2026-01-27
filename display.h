//
// Created by MG on 17/12/2025.
//

#ifndef WISIELEC_DISPLAY_H
#define WISIELEC_DISPLAY_H

#include "categories_logic.h"
#include "models.h"

// Tutaj umieszczamy deklaracje wszystkich funkcji, które będą coś wypisywać na ekran
void drawMenu(const std::string &playerName, const std::string &categoryName);
void drawGameStatus(const Player &player, const Player &cpu, const Keyword &keyword, const Category &cat);
void drawHangman(int lives);

void drawLeaderboard(const std::vector<std::vector<std::string>> &leaderboardData);

// Funkcje obsługujące wyświetlanie tekstu w kolorze

/*
 * ANSI COLOR CODES:
 * dark red = 31
 * dark green = 32
 * dark yellow = 33
 * dark blue = 34
 * dark magenta = 35
 * dark cyan = 36
 * dark white = 37
 * light red = 91
 * light green = 92
 * light yellow = 93
 * light blue = 94
 * light magenta = 95
 * light cyan = 96
 * light white = 97
 */

enum class Colors {
    Red = 31,
    Green = 92,
    Blue = 34,
    Yellow = 33,
    Magenta = 35,
    Cyan = 36,
    White = 97,
    Reset = 0
};

std::string colorString(const std::string &text, Colors col, bool isBold = false);

// Funkcje manipulujące tekstem
void printBr(const std::string &text);

void drawLine(const int &length, const std::string &text, Colors col, bool isBold);

#endif //WISIELEC_DISPLAY_H