//
// Created by MG on 17/12/2025.
//

#include "display.h"
#include <iostream>

// Funkcje obsługujące wyświetlanie tekstu w kolorze
std::string colorString(const std::string &text, const Colors col, const bool isBold) {
    const std::string reset = "\033[0m";
    std::string prefix = "\033[";

    if (isBold) {
        prefix += "1;";
    }

    prefix += std::to_string(static_cast<int>(col)) + "m";

    return prefix + text + reset;

}

// Funkcje manipulujące tekstem
void printBr(const std::string &text) {
    std::cout << text << std::endl;
}

// Funkcje wyświetlające różne elementy gry
void drawMenu(const std::string &playerName, const std::string &categoryName) {
    system("clear");

    printBr(colorString("---------------- WISIELEC ----------------", Colors::Red, true));
    printBr("Witaj, " + colorString(playerName, Colors::Cyan));
    printBr("Wybrana kategoria: " + colorString(categoryName, Colors::Yellow));
    printBr("Wpisz liczbę, aby wybrać pozycję w menu.");
    printBr("1. Rozpocznij rozgrywkę");
    printBr("2. Wybierz kategorię");
    printBr("3. Zmień nazwę gracza");
    printBr("4. Tablica wyników");
    printBr("5. Instrukcja gry");
    printBr("6. Zakończ grę");
    printBr(colorString("------------------------------------------", Colors::Red, true));
}

void drawGameStatus(const Player &player, const Player &cpu, const Keyword &keyword, const Category &cat) {
    system("clear");

    std::cout << "Kategoria: " << colorString(categoryToString(cat), Colors::Yellow) << std::endl;
    std::cout << "==========================" << std::endl;
    std::cout << "Graczowi " << colorString(player.nickname, Colors::Cyan) << " pozostało " << player.livesLeft << " żyć." << std::endl;
    std::cout << "Komputerowi pozostało " << cpu.livesLeft << " żyć." << std::endl;


    std::cout << std::endl;
    std::cout << colorString("Użyte litery: ", Colors::Magenta);
    for (int i = 0; const char c : player.usedLetters) {
        if (i > 0) std::cout << ", ";
        std::cout << "[" << c << "]";
        i++;
    }
    std::cout << std::endl;

    std::cout << "Hasło:" << std::endl;
    for (int i = 0; i < keyword.length; i++) {
        if (i != 0) std::cout << " ";
        if (player.usedLetters.contains(keyword.word[i])) {
            std::cout << keyword.word[i];
        } else {
            std::cout << "_";
        }
    }

    std::cout << std::endl;
    if (player.livesLeft < 12) drawHangman(player.livesLeft);


    std::cout << std::endl;
}

// funkcja rysująca etapy szubienicy
void drawHangman(const int lives) {
    printBr(colorString("=================", Colors::Yellow)); // góra jest zawsze

    if (lives == 11) {
        printBr(colorString("                 ", Colors::Yellow));
        printBr(colorString("                 ", Colors::Yellow));
        printBr(colorString("                 ", Colors::Yellow));
        printBr(colorString("                 ", Colors::Yellow));
        printBr(colorString("                 ", Colors::Yellow));
        printBr(colorString("                 ", Colors::Yellow));
        printBr(colorString("   /             ", Colors::Yellow));
        printBr(colorString("  /               ", Colors::Yellow));
    } else if (lives == 10) {
        printBr(colorString("                 ", Colors::Yellow));
        printBr(colorString("                 ", Colors::Yellow));
        printBr(colorString("                 ", Colors::Yellow));
        printBr(colorString("                 ", Colors::Yellow));
        printBr(colorString("                 ", Colors::Yellow));
        printBr(colorString("                 ", Colors::Yellow));
        printBr(colorString("   / \\           ", Colors::Yellow));
        printBr(colorString("  /   \\           ", Colors::Yellow));
    } else if (lives == 9) {
        printBr(colorString("    +            ", Colors::Yellow));
        printBr(colorString("    |            ", Colors::Yellow));
        printBr(colorString("    |            ", Colors::Yellow));
        printBr(colorString("    |            ", Colors::Yellow));
        printBr(colorString("    |            ", Colors::Yellow));
        printBr(colorString("    |            ", Colors::Yellow));
        printBr(colorString("   / \\           ", Colors::Yellow));
        printBr(colorString("  /   \\           ", Colors::Yellow));
    } else if (lives == 8) {
        printBr(colorString("    +            ", Colors::Yellow));
        printBr(colorString("    | /          ", Colors::Yellow));
        printBr(colorString("    |/           ", Colors::Yellow));
        printBr(colorString("    |            ", Colors::Yellow));
        printBr(colorString("    |            ", Colors::Yellow));
        printBr(colorString("    |            ", Colors::Yellow));
        printBr(colorString("   / \\           ", Colors::Yellow));
        printBr(colorString("  /   \\           ", Colors::Yellow));
    } else if (lives == 7) {
        printBr(colorString("    +_______+    ", Colors::Yellow));
        printBr(colorString("    | /          ", Colors::Yellow));
        printBr(colorString("    |/           ", Colors::Yellow));
        printBr(colorString("    |            ", Colors::Yellow));
        printBr(colorString("    |            ", Colors::Yellow));
        printBr(colorString("    |            ", Colors::Yellow));
        printBr(colorString("   / \\           ", Colors::Yellow));
        printBr(colorString("  /   \\           ", Colors::Yellow));
    } else if (lives == 6) {
        printBr(colorString("    +_______+    ", Colors::Yellow));
        printBr(colorString("    | /     |    ", Colors::Yellow));
        printBr(colorString("    |/           ", Colors::Yellow));
        printBr(colorString("    |            ", Colors::Yellow));
        printBr(colorString("    |            ", Colors::Yellow));
        printBr(colorString("    |            ", Colors::Yellow));
        printBr(colorString("   / \\           ", Colors::Yellow));
        printBr(colorString("  /   \\           ", Colors::Yellow));
    } else if (lives == 5) {
        printBr(colorString("    +_______+    ", Colors::Yellow));
        printBr(colorString("    | /     |    ", Colors::Yellow));
        printBr(colorString("    |/    (o.o)  ", Colors::Yellow));
        printBr(colorString("    |            ", Colors::Yellow));
        printBr(colorString("    |            ", Colors::Yellow));
        printBr(colorString("    |            ", Colors::Yellow));
        printBr(colorString("   / \\           ", Colors::Yellow));
        printBr(colorString("  /   \\           ", Colors::Yellow));
    } else if (lives == 4) {
        printBr(colorString("    +_______+    ", Colors::Yellow));
        printBr(colorString("    | /     |    ", Colors::Yellow));
        printBr(colorString("    |/    (o.o)  ", Colors::Yellow));
        printBr(colorString("    |       |    ", Colors::Yellow));
        printBr(colorString("    |            ", Colors::Yellow));
        printBr(colorString("    |            ", Colors::Yellow));
        printBr(colorString("   / \\           ", Colors::Yellow));
        printBr(colorString("  /   \\           ", Colors::Yellow));
    } else if (lives == 3) {
        printBr(colorString("    +_______+    ", Colors::Yellow));
        printBr(colorString("    | /     |    ", Colors::Yellow));
        printBr(colorString("    |/    (o.o)  ", Colors::Yellow));
        printBr(colorString("    |      /|    ", Colors::Yellow));
        printBr(colorString("    |            ", Colors::Yellow));
        printBr(colorString("    |            ", Colors::Yellow));
        printBr(colorString("   / \\           ", Colors::Yellow));
        printBr(colorString("  /   \\           ", Colors::Yellow));
    } else if (lives == 2) {
        printBr(colorString("    +_______+    ", Colors::Yellow));
        printBr(colorString("    | /     |    ", Colors::Yellow));
        printBr(colorString("    |/    (o.o)  ", Colors::Yellow));
        printBr(colorString("    |      /|\\   ", Colors::Yellow));
        printBr(colorString("    |            ", Colors::Yellow));
        printBr(colorString("    |            ", Colors::Yellow));
        printBr(colorString("   / \\           ", Colors::Yellow));
        printBr(colorString("  /   \\           ", Colors::Yellow));
    } else if (lives == 1) {
        printBr(colorString("    +_______+    ", Colors::Yellow));
        printBr(colorString("    | /     |    ", Colors::Yellow));
        printBr(colorString("    |/    (o.o)  ", Colors::Yellow));
        printBr(colorString("    |      /|\\   ", Colors::Yellow));
        printBr(colorString("    |      /     ", Colors::Yellow));
        printBr(colorString("    |            ", Colors::Yellow));
        printBr(colorString("   / \\           ", Colors::Yellow));
        printBr(colorString("  /   \\           ", Colors::Yellow));
    } else if (lives == 0) {
        printBr(colorString("    +_______+    ", Colors::Yellow));
        printBr(colorString("    | /     |    ", Colors::Yellow));
        printBr(colorString("    |/    (o.o)  ", Colors::Yellow));
        printBr(colorString("    |      /|\\   ", Colors::Yellow));
        printBr(colorString("    |      / \\   ", Colors::Yellow));
        printBr(colorString("    |            ", Colors::Yellow));
        printBr(colorString("   / \\           ", Colors::Yellow));
        printBr(colorString("  /   \\           ", Colors::Yellow));
    }

    printBr(colorString("=================", Colors::Yellow)); // dół też jest zawsze // dół też jest zawsze
}

void drawLeaderboard(const std::vector<std::vector<std::string>> &leaderboardData) {
    printBr(colorString("------------ TABLICA WYNIKÓW ------------", Colors::Red, true));
    std::cout << std::setw(18) << std::left << "Nazwa gracza";
    std::cout << " ";
    std::cout << std::setw(19) << std::right << "Rozegranych gier";
    std::cout << " ";
    std::cout << std::setw(17) << std::right << "Wygranych gier";
    std::cout << " ";
    std::cout << std::setw(15) << std::right << " Suma punktów";
    std::cout << std::endl;

    for (std::vector vector : leaderboardData) {
        printBr(colorString("-----------------------------------------", Colors::Red));
        std::cout << std::setw(18) << std::left << vector[0];
        std::cout << " ";
        std::cout << std::setw(19) << std::right << vector[1];
        std::cout << " ";
        std::cout << std::setw(17) << std::right << vector[2];
        std::cout << " ";
        std::cout << std::setw(14) << std::right << vector[3];
        std::cout << std::endl;
    }

    printBr(colorString("-----------------------------------------", Colors::Red, true));
}
