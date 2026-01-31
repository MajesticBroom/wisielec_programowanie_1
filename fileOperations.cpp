//
// Created by MG on 22/12/2025.
//

#include "fileOperations.h"

#include <algorithm>
#include <fstream>
#include <iostream>

std::vector<std::vector<std::string>> readFromLeaderboardFile() {
    // Tutaj będzie kod czytający z pliku tablicy wyników
    // std::vector<std::vector<std::string>> dummyData = {
    //     {"Gracz1", "5", "150"},
    //     {"Gracz2", "3", "90"},
    //     {"Gracz3", "7", "210"}
    // };
    //
    // return dummyData;

    std::ifstream file("results/leaderboard.txt");

    if (!file.is_open()) {
        std::cerr << "Nie udało się otworzyć pliku z tablicą wyników!" << std::endl;
        return {};
    }

    std::vector<std::vector<std::string>> leaderboardData;

    std::string nickname;
    int matchesPlayed, matchesWon, totalPoints;

    while (file >> nickname >> matchesPlayed >> matchesWon >> totalPoints) {
        std::vector<std::string> row;
        row.push_back(nickname);
        row.push_back(std::to_string(matchesPlayed));
        row.push_back(std::to_string(matchesWon));
        row.push_back(std::to_string(totalPoints));

        leaderboardData.push_back(row);
    }

    file.close();

    // Sortujemy od początku (begin) do końca (end) wektora
    std::sort(leaderboardData.begin(), leaderboardData.end(),
        [](const std::vector<std::string>& a, const std::vector<std::string>& b) {
            // totalPoints znajduje się pod indeksem 3
            // Musimy użyć std::stoi, aby zamienić string na int do poprawnego porównania
            int pointsA = std::stoi(a[3]);
            int pointsB = std::stoi(b[3]);

            // Zwracamy true, jeśli A ma być przed B
            // Dla sortowania malejącego (max -> min): A > B
            return pointsA > pointsB;
        }
    );

    return leaderboardData;
}

std::vector<std::string> getLatestGameSettings() {
    std::ifstream file("results/lastGame.txt");

    if (!file.is_open()) {
        std::cerr << "Nie udało się otworzyć pliku z ustawieniami gry!" << std::endl;
        return {};
    }

    std::vector<std::string> settings;
    std::string line;

    while (std::getline(file, line)) {
        settings.push_back(line);
    }

    file.close();

    return settings;
}

void saveLatestGameSettings(const Player &player, const Category &cat) {
    std::ofstream file("results/lastGame.txt");

    if (!file.is_open()) {
        std::cerr << "Nie udało się otworzyć pliku do zapisu ustawień gry!" << std::endl;
        return;
    }

    if (player.nickname == "Gracz") {
        file << "0" << std::endl;
    } else {
        file << "1" << std::endl;
        file << player.nickname << std::endl;
        file << static_cast<int>(cat) << std::endl;
    }




    file.close();
}

void updateLeaderboard(std::vector<std::vector<std::string>> &leaderboardData, const Player &player) {
    bool found = false;

    for (auto &row : leaderboardData) {
        if (!row.empty() && row[0] == player.nickname) {
            // Zaktualizuj istniejący wpis
            row[1] = std::to_string(player.matchesPlayed);
            row[2] = std::to_string(player.matchesWon);
            row[3] = std::to_string(player.totalPoints);
            found = true;
            break;
        }
    }

    if (!found) {
        const std::vector<std::string> newRow = {
            player.nickname,
            std::to_string(player.matchesPlayed),
            std::to_string(player.matchesWon),
            std::to_string(player.totalPoints)
        };

        leaderboardData.push_back(newRow);
    }

    std::ofstream file("results/leaderboard.txt");
    if (!file.is_open()) {
        std::cerr << "Nie udało się otworzyć pliku do zapisu tablicy wyników!" << std::endl;
        return;
    }

    for (const auto &row : leaderboardData) {
        if (row.size() == 4) {
            file << row[0] << " " << row[1] << " " << row[2] << " " << row[3] << std::endl;
        }
    }

    file.close();
}

PlayerStats loadPlayerStats(const std::string &nickname) {
    std::vector<std::vector<std::string>> allData = readFromLeaderboardFile();
    PlayerStats stats;

    for (const auto &row : allData) {
        if (!row.empty() && row[0] == nickname) {
            stats.matchesPlayed = std::stoi(row[1]);
            stats.matchesWon = std::stoi(row[2]);
            stats.totalPoints = std::stoi(row[3]);
            break;
        } else {
            stats.matchesPlayed = 0;
            stats.matchesWon = 0;
            stats.totalPoints = 0;
        }
    }

    return stats;
}
