#include "game_logic.h"
#include <chrono>
#include <iostream>
#include <random>
#include <set>
#include <thread>

#include "display.h"


int getRandomInt(const int from, const int to) {
    // wykorzytujemy Mersenne Twister do generowania liczb losowych
    std::mt19937 generator(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> dist(from, to);

    return dist(generator);
}

std::string getRandomWord(const Category selectedCategory) {
    // wczytujemy słowa z pliku do wektora, na bazie wybranej kategorii
    std::vector<std::string> words = loadCategory(selectedCategory);

    const int randomIndex = getRandomInt(0, words.size() - 1);

    if (words.empty()) {
        return "";
    }

    // zwracamy słowo o wylosowanym indeksie w tablicy
    return words[randomIndex];
}

Keyword createKeyword(const std::string &wordFromBank) {
    Keyword newKeyword;
    newKeyword.word = wordFromBank;
    newKeyword.length = wordFromBank.length();

    return newKeyword;
}

bool isAlive(const Player &player) {
    if (player.livesLeft > 0) {
        return true;
    }

    return false;
}

bool hasWon(Player &player, const Keyword &keyword) {
    if (player.correctlyGuessedLetters == keyword.length) {
        player.points += 10; // punkty za wygraną
        return true;
    }

    return false;
}

void resetPlayerState(Player &player) {
    // przywracamy stan początkowy gracza/komputera dla nowej rundy
    player.livesLeft = 12;
    player.correctlyGuessedLetters = 0;
    player.usedLetters = {};
    player.points = 0;
}

void validateInput(std::string &input) {

    // dodajemy cząstki słów zakazanych, aby zapobiec wulgaryzmom w inpucie.
    const std::vector<std::string> bannedWords = {
        "kurw",
        "chuj",
        "pizd",
        "jeb",
        "pierdol",
        "spierd"
    };

    bool isValid = false;

    while (!isValid) {
        std::string lowerInput = input;
        std::transform(lowerInput.begin(), lowerInput.end(), lowerInput.begin(), [](unsigned char c){return std::tolower(c);});
        const int asciiValue = static_cast<int>(input.front());
        const char firstChar = input.front();

        if (input.empty()) {
            // Pusty input
            std::cout << "Proszę wprowadzić znak!" << std::endl;
        } else {
            bool containsBanned = false;
            for (const std::string &bannedWord : bannedWords) {
                if (lowerInput.find(bannedWord) != std::string::npos) {
                    containsBanned = true;
                    break;
                }
            }

            if (containsBanned) {
                // gdy input zawiera wulgaryzm
                std::cout << colorString("JAK TY SIĘ WYRAŻASZ?!", Colors::Red) << " Spróbuj ponownie." << std::endl;
            } else if (input.length() > 1) {
                // gdy input zawiera ciąg znaków
                std::cout << "Wpisz tylko jeden symbol!" << std::endl;
            }
            else if (firstChar == '0' || firstChar == '1' || firstChar == '2' || firstChar == '3') {
                // gdy input zawiera cyfrę służącą do nawigacji w menu
                isValid = true;
                continue;
            } else if (!std::isalpha(static_cast<unsigned char>(firstChar))) {
                // gdy input nie jest literą
                std::cout << "Wprowadzony znak nie jest literą! Spróbuj ponownie." << std::endl;
            } else {
                isValid = true;
                continue;
            }
        }

        std::cout << "Podaj znak: ";
        std::cin >> input;
    }
}

char getPlayerInput() {
    std::string input;
    std::cout << "[0] - Anuluj grę, [1] - Kontynuuj rundę, [2] - Resetuj rundę, [3] - Odgadnij całe hasło" << std::endl;
    std::cout << "Podaj znak: ";
    std::cin >> input;

    validateInput(input);

    const char inputChar = std::isupper(input.front()) ? static_cast<char>(std::tolower(input.front())) : input.front();

    return inputChar;
}

void processGuess(Player &player, const Keyword &keyword, const char guess) {
    int occurrences = static_cast<int>(std::count(keyword.word.begin(), keyword.word.end(), guess));

    // Jeśli litera znajduje się w haśle:
    if (occurrences > 0) {
        // Jeśli gracz nie posiada tej litery w zbiorze wcześniej użytych
        if (!(player.usedLetters.contains(guess))) {
            // Gracz dostaje punkty za każde wystąpienie litery
            player.correctlyGuessedLetters += occurrences;
            player.points += occurrences * 5;
        } else {
            player.livesLeft--; // gdy gracz wpisze literę, którą już wpisał
        }

    } else {
        player.livesLeft--;
    }

    // Wpisaną literę zawsze dodajemy do użytych przez użytkownika, aby nie dostawał punktów za ponowne wpisanie.
    player.usedLetters.insert(guess);
}



char getComputerMove(const Player &computer) {
    char randomChar;

    do {
        // losujemy literę od nowa, jeśli ta była już użyta przez komputer
        randomChar = static_cast<char>(getRandomInt(97, 122));
    } while (computer.usedLetters.contains(randomChar));

    return randomChar;
}
