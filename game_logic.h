#ifndef WISIELEC_GAME_LOGIC_H
#define WISIELEC_GAME_LOGIC_H

#include "models.h"
#include "categories_logic.h"
#include <random>
#include <chrono>



int getRandomInt(int from, int to);

std::string getRandomWord(Category selectedCategory);
Keyword createKeyword(const std::string &wordFromBank);

bool isAlive(const Player &player);
bool hasWon(Player &player, const Keyword &keyword);

void resetPlayerState(Player &player);

char getPlayerInput();
void processGuess(Player &player, const Keyword &keyword, char guess);
void validateInput(std::string &input);

char getComputerMove(const Player &computer);


#endif //WISIELEC_GAME_LOGIC_H