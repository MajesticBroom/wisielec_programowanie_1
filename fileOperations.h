//
// Created by MG on 22/12/2025.
//

#ifndef WISIELEC_FILEOPERATIONS_H
#define WISIELEC_FILEOPERATIONS_H

#include "categories_logic.h"
#include "models.h"

std::vector<std::vector<std::string>> readFromLeaderboardFile();

std::vector<std::string> getLatestGameSettings();

void saveLatestGameSettings(const Player &player, const Category &cat);

void updateLeaderboard(std::vector<std::vector<std::string>> &leaderboardData, const Player &player);

PlayerStats loadPlayerStats(const std::string &nickname);

#endif //WISIELEC_FILEOPERATIONS_H