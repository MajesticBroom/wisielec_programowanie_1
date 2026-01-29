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

    printBr(colorString("=================", Colors::Yellow)); // dół też jest zawsze
}

const std::string linia = "-----------------------------------------------------------------------";

void drawLine(const int &length, const std::string &text = "", const Colors col = Colors::White, const bool isBold = false) {
    if (length > 0) {
        std::string line = "";
        if (text.empty()) {
            for (int i = 0; i < length; i++) {
                line += "-";
            }
        } else {
            std::string part = "";
            int partLength = (length - text.length()) / 2;
            for (int i = 0; i < partLength; i++) {
                if (i == (partLength - 1)) {
                    line += " ";
                } else {
                    line += "-";
                }
            }

            line += text;

            for (int i = 0; i < partLength; i++) {
                if (i == 0) {
                    line += " ";
                } else {
                    line += "-";
                }
            }
        }

        std::cout << colorString(line, col, isBold) << std::endl;
    }
}

void drawLeaderboard(const std::vector<std::vector<std::string>> &leaderboardData) {
    drawLine(71, "Tablica wynikow", Colors::Red, true);
    std::cout << std::setw(18) << std::left << "Nazwa gracza";
    std::cout << " ";
    std::cout << std::setw(19) << std::right << "Rozegranych gier";
    std::cout << " ";
    std::cout << std::setw(17) << std::right << "Wygranych gier";
    std::cout << " ";
    std::cout << std::setw(15) << std::right << " Suma punktów";
    std::cout << std::endl;

    for (std::vector vector : leaderboardData) {
        drawLine(71, "", Colors::Red, true);
        std::cout << std::setw(18) << std::left << vector[0];
        std::cout << " ";
        std::cout << std::setw(19) << std::right << vector[1];
        std::cout << " ";
        std::cout << std::setw(17) << std::right << vector[2];
        std::cout << " ";
        std::cout << std::setw(14) << std::right << vector[3];
        std::cout << std::endl;
    }

    drawLine(71, "", Colors::Red, true);
}

void displayInstructions() {
    drawLine(90, "INSTRUKCJA", Colors::Red, true);
    std::cout << std::endl;

    std::cout << " Gra polega na odgadywaniu wylosowanego hasła. Hasłem jest jednowyrazowe" << std::endl;
    std::cout << " słowo w języku polskim, pozbawione polskich znaków specjalnych" << std::endl;
    std::cout << " (np. w haśle występuje \"a\" zamiast \"ą\")." << std::endl;
    std::cout << std::endl;
    std::cout << " Mechanika gry wyróżnia się następującymi cechami:" << std::endl;
    std::cout << std::endl;

    std::cout << "  - Każda ze stron (Gracz i Komputer) posiada pulę 12 żyć," << std::endl;
    std::cout << "    odpowiadającą liczbie etapów rysowania pełnej szubienicy." << std::endl;
    std::cout << std::endl;

    std::cout << "  - Celem jest odgadnięcie hasła szybciej niż przeciwnik komputerowy." << std::endl;
    std::cout << std::endl;

    std::cout << "    (+) Prawidłowa litera: ........................ +5 pkt" << std::endl;
    std::cout << "    (-) Błędna litera: ............................ -1 życie" << std::endl;
    std::cout << "    (+) Udana próba odgadnięcia całego hasła: ..... +3 pkt (za odwagę)" << std::endl;
    std::cout << "    (-) Nieudana próba odgadnięcia całego hasła: .. -3 życia" << std::endl;
    std::cout << "    (+) Ostateczne odgadnięcie hasła: ............. +10 pkt" << std::endl;
    std::cout << std::endl;

    std::cout << "  Gra kończy się w jednym z czterech przypadków:" << std::endl;
    std::cout << "    1. Gracz odgadł hasło ................ Zwycięstwo Gracza" << std::endl;
    std::cout << "    2. Komputer stracił wszystkie życia .. Zwycięstwo Gracza" << std::endl;
    std::cout << "    3. Komputer odgadł hasło ............. Zwycięstwo Komputera" << std::endl;
    std::cout << "    4. Gracz stracił wszystkie życia ..... Zwycięstwo Komputera" << std::endl;
    std::cout << std::endl;

    std::cout << "  Gracz porusza się po interfejsie za pomocą wybierania odpowiednich" << std::endl;
    std::cout << "  cyfr opisanych na ekranie, np.:" << std::endl;
    // std::cout << "     [0] - Wróć do menu" << std::endl;
    std::cout << colorString("     [0] - Wróć do menu", Colors::Blue) << std::endl;
    std::cout << "  Użytkownik powinien wprowadzić odpowiednią cyfrę z klawiatury," << std::endl;
    std::cout << "  po czym zatwierdzić ją klawiszem ENTER/RETURN. Na tej samej zasadzie" << std::endl;
    std::cout << "  użytkownik wprowadza kolejne litery w trakcie rozgrywki." << std::endl;
    std::cout << std::endl;

    drawLine(90, "", Colors::Red, true);
}