#include <iostream>
#include "models.h"
#include "display.h"
#include "game_logic.h"
#include "settings.h"
#include "categories_logic.h"
#include "fileOperations.h"


#include <random>
#include <chrono>
#include <thread>


using namespace std;


int main() {
    // Mateusz Gębka, gr. 2/4

    std::vector<std::string> latestSettings = getLatestGameSettings();

    Player player;
    Player cpu;
    Category currentCategory;

    cout << "Witaj w grze Wisielec!" << endl;
    cout << "Podaj swój nick lub wprowadź [0], aby grać jako \"Gracz\": ";
    string inputNickname;
    cin >> inputNickname;

    if (inputNickname != "0") {

        while (inputNickname.length() < 3 || inputNickname.length() > 18) {
            cout << "Nick musi mieć od 3 do 18 znaków! Spróbuj ponownie." << endl;
            cout << "Podaj swój nick lub wprowadź [0], aby grać jako \"Gracz\": ";
            cin >> inputNickname;
        }

        if (latestSettings.size() > 1) {
            if (latestSettings[1] == inputNickname) {
                currentCategory = static_cast<Category>(std::stoi(latestSettings[2]));
            } else {
                currentCategory = Category::Mix;
            }
        } else {
            currentCategory = Category::Mix;
        }

        PlayerStats stats = loadPlayerStats(inputNickname);

        player = {inputNickname, {}, 0, 12, 0};
        player.matchesPlayed = stats.matchesPlayed;
        player.matchesWon = stats.matchesWon;
        player.totalPoints = stats.totalPoints;

        std::vector<std::vector<std::string>> leaderboardData = readFromLeaderboardFile();
        updateLeaderboard(leaderboardData, player);

    } else {
        currentCategory = Category::Mix;
        player = {"Gracz", {}, 0, 12};
    }

    cpu = {"Komputer", {}, 0, 12};

    // Wczytujemy ostatniego gracza i kategorię z pliku ustawień, jeśli nie był to "Gracz", czyli no-name
    // if (latestSettings.empty() || !static_cast<bool>(std::stoi(latestSettings[0]))) {
    //     player = {"Gracz", {}, 0, 12};
    //     currentCategory = Category::Mix;
    //
    // } else {
    //     player = {latestSettings[1], {}, 0, 12};
    //     cpu = {"Komputer", {}, 0, 12};
    //     currentCategory = static_cast<Category>(std::stoi(latestSettings[2]));
    // }



    int menuChoice = 0;

    do {
        drawMenu(player.nickname, categoryToString(currentCategory));
        // cout << colorString("Testowy pogrubiony czerwony napis", Colors::Red, true);

        // walidacja wyboru menu
        if (!(std::cin >> menuChoice)) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            menuChoice = -1; // wymuszenie wejścia do default
        }

        system("clear");

        switch (menuChoice) {
            case 1: {
                bool playAgain = true;
                bool stopGame = false;
                while (playAgain) {
                    // pętla gry
                    string rawWord = getRandomWord(currentCategory);
                    Keyword secret = createKeyword(rawWord);
                    // Keyword secret = {"dupa", 4};

                    resetPlayerState(player);
                    resetPlayerState(cpu);


                    // // Tutaj można dodać jeszcze odliczanie dzięki pętli for
                    // // cout << "Rozpoczynamy grę!" << endl;
                    // cout << "Pamiętaj, że hasła nie zawierają polskich znaków!" << endl;
                    //
                    // std::cout << "Rozpoczynamy grę" << std::flush;
                    // std::this_thread::sleep_for(std::chrono::milliseconds(600));
                    //
                    // for (int i = 3; i > 0; i--) {
                    //     std::cout << "." << std::flush;
                    //     std::this_thread::sleep_for(std::chrono::milliseconds(600));
                    // }
                    // // Wstrzymanie na chwilę, aby użytkownik zdążył przeczytać
                    // std::this_thread::sleep_for(std::chrono::milliseconds(200));
                    //
                    // system("clear");


                    // pętla rozgrywki:
                    while (isAlive(player) && isAlive(cpu) && !hasWon(player, secret) && !hasWon(cpu, secret)) {

                        drawGameStatus(player, cpu, secret, currentCategory);

                        // Tura gracza
                        char playerGuess = getPlayerInput();
                        // walidacja jest wewnątrz getPlayerInput()

                        // obsługa użycia cyfr do nawigacji
                        if (playerGuess == '0') {
                            playAgain = false;
                            stopGame = true;
                            resetPlayerState(player);
                            resetPlayerState(cpu);
                            break;
                        } else if (playerGuess == '1') {
                            system("clear");
                            continue;
                        } else if (playerGuess == '2') {
                            rawWord = getRandomWord(currentCategory);

                            // walidacja, czy nowe słowo nie jest puste
                            if (rawWord.empty()) {
                                cout << colorString("Błąd ładowania nowego słowa z kategorii " + categoryToString(currentCategory) + ". Wybierz inną kategorię w menu.", Colors::Red) << endl;
                                playAgain = false;
                                stopGame = true;
                                resetPlayerState(player);
                                resetPlayerState(cpu);
                                break;
                            }

                            secret = createKeyword(rawWord);
                            resetPlayerState(player);
                            resetPlayerState(cpu);
                            system("clear");
                            continue;
                        } else if (playerGuess == '3') {
                            std::string userFullWord;
                            std::cout << "Podaj całe hasło (Wpisz 'X', aby anulować wpisywanie całego słowa): ";
                            std::cin >> userFullWord;

                            if (userFullWord == "X") {
                                playerGuess = 1;
                                continue;
                            }

                            // zmiana liter na małe
                            std::string userFullWordLower = userFullWord;
                            transform(userFullWordLower.begin(), userFullWordLower.end(), userFullWordLower.begin(), ::tolower);

                            if (userFullWordLower == secret.word) {
                                std::cout << colorString("Brawo! To poprawne hasło!", Colors::Green) << std::endl;
                                // Gracz odgadł całe hasło
                                for (char c : secret.word) {
                                    if (!player.usedLetters.contains(c)) {
                                        player.usedLetters.insert(c);
                                        player.points += 5; // punkty za każdą odgadniętą literę
                                    }
                                }

                                player.correctlyGuessedLetters = secret.length;

                                player.points += 10; // punkty za odwagę

                                // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                            } else {
                                std::cout << colorString("Niestety, to nie to hasło. Tracisz dwa życia.", Colors::Red) << std::endl;
                                player.livesLeft -= 2; // kara za błędne odgadnięcie
                                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                            }

                            system("clear");
                            continue; // pomijamy przetwarzanie wpisanej '3' jako znaku
                        }

                        processGuess(player, secret, playerGuess);

                        drawGameStatus(player, cpu, secret, currentCategory);



                        // Tura komputera, tylko jeśli gracz jeszcze nie wygrał i nadal żyje
                        if (!hasWon(player, secret) && isAlive(player)) {

                            // // Tutaj można dodać imitacje "myślenia" komputera przez ~1.5 sek
                            // std::cout << "Komputer wykonuje swój ruch" << std::flush;
                            // std::this_thread::sleep_for(std::chrono::milliseconds(600));
                            //
                            // for (int i = 3; i > 0; i--) {
                            //     std::cout << "." << std::flush;
                            //     std::this_thread::sleep_for(std::chrono::milliseconds(600));
                            // }
                            // // Wstrzymanie na chwilę, aby użytkownik zdążył przeczytać
                            // std::this_thread::sleep_for(std::chrono::milliseconds(200));
                            //
                            // system("clear");

                            char cpuGuess = getComputerMove(cpu);
                            // char cpuGuess = getPlayerInput(); // dla celów testowych

                            processGuess(cpu, secret, cpuGuess);

                        }
                    }

                    // Ostatni widok gry
                    drawGameStatus(player, cpu, secret, currentCategory);

                    // Zakończenie rundy
                    if (hasWon(player, secret) && isAlive(cpu)) {
                        cout << colorString("Odgadłeś hasło. Wygrałeś!", Colors::Green) << endl;
                        player.totalPoints += player.points;
                        player.matchesWon++;
                        player.matchesPlayed++;
                    } else if (!isAlive(cpu)) {
                        cout << colorString("Komputer przegrał. Wygrałeś!", Colors::Green) << endl;
                        cout << "Poprawne hasło: " << colorString(secret.word, Colors::Green) << endl;
                        player.totalPoints += player.points;
                        player.matchesWon++;
                        player.matchesPlayed++;
                    } else if (!isAlive(player)) {
                        cout << colorString("Skończyły Ci się życia. Przegrałeś!", Colors::Red) << endl;
                        cout << "Poprawne hasło: " << colorString(secret.word, Colors::Green) << endl;
                        player.totalPoints += player.points;
                        player.matchesPlayed++;
                    } else if (hasWon(cpu, secret) && isAlive(player)) {
                        cout << colorString("Komputer odgadł hasło. Przegrałeś!", Colors::Red) << endl;
                        cout << "Poprawne hasło: " << colorString(secret.word, Colors::Green) << endl;
                        player.totalPoints += player.points;
                        player.matchesPlayed++;
                    }

                    saveLatestGameSettings(player, currentCategory);

                    // Aktualizacja tablicy wyników
                    if (player.nickname != "Gracz") {
                        std::vector<std::vector<std::string>> leaderboardData = readFromLeaderboardFile();
                        updateLeaderboard(leaderboardData, player);
                    }

                    if (stopGame == false) {
                        cout << endl;

                        int postGameChoice;
                        do {
                            cout << "Co dalej?" << endl;
                            cout << "[0] - powrót do menu" << endl;
                            cout << "[1] - graj ponownie" << endl;

                            if (!(std::cin>> postGameChoice)) {

                                std::cin.clear();
                                std::cin.ignore(1000, '\n');
                                postGameChoice = -1; // wymuszenie powtórzenia pętli
                            }

                        } while (postGameChoice != 0 && postGameChoice != 1);

                        if (postGameChoice == 0) {
                            playAgain = false;
                            menuChoice = 0;
                        }

                    }

                    system("clear");
                }
                break;
            }

            case 2: {
                // Zmiana kategorii
                std::string categoryChoice;

                cout << "Zmiana kategorii" << endl;
                for (Category cat : {Category::Animals, Category::Electronics, Category::Fruits, Category::SchoolSubjects, Category::Mix}) {
                    cout << "[" << static_cast<int>(cat) + 1 << "] - " << categoryToString(cat) << endl;
                }
                cout << "[0] - Anuluj" << endl;

                cout << "Wybierz kategorię: ";
                cin >> categoryChoice;

                if (categoryChoice.empty() || categoryChoice == "0") {
                    menuChoice = 0;
                } else {
                    currentCategory = static_cast<Category>(stoi(categoryChoice) - 1);
                    menuChoice = 0;
                }

                system("clear");


                break;
            }

            case 3: {
                cout << "[0] - Anuluj" << endl;
                string newNickname;
                cout << "Zmień nick: ";
                cin >> newNickname;

                if (newNickname.empty() || newNickname == "0") {
                    menuChoice = 0;
                } else {
                    while (newNickname.length() < 3 || newNickname.length() > 18) {
                        cout << "Nick powinien mieć od 3 do 18 liter." << endl;
                        cout << "Zmień nick: ";
                        cin >> newNickname;
                    }

                    PlayerStats stats = loadPlayerStats(newNickname);

                    player = {newNickname, {}, 0, 12, 0};
                    player.matchesPlayed = stats.matchesPlayed;
                    player.matchesWon = stats.matchesWon;
                    player.totalPoints = stats.totalPoints;

                    std::vector<std::vector<std::string>> leaderboardData = readFromLeaderboardFile();
                    updateLeaderboard(leaderboardData, player);


                    changePlayerNickname(player, newNickname);


                }

                currentCategory = Category::Mix;
                system("clear");
                break;
            }

            case 4: {
                // Leaderboard
                drawLeaderboard(readFromLeaderboardFile());

                std::cout << "[0] - Powrót do menu" << std::endl;
                int menuMove;
                std::cin >> menuMove;
                // std::cin >> menuChoice;

                while (menuMove != 0) {
                    std::cout << "Niedostępna opcja do wyboru!" << std::endl;
                    std::cin >> menuMove;
                }

                menuChoice = menuMove;
                system("clear");

                break;
            }

            case 5: {
                displayInstructions();

                std::cout << "[0] - Powrót do menu" << std::endl;
                int menuMove;
                std::cin >> menuMove;
                // std::cin >> menuChoice;

                while (menuMove != 0) {
                    std::cout << "Niedostępna opcja do wyboru!" << std::endl;
                    std::cin >> menuMove;
                }

                menuChoice = menuMove;
                system("clear");

                break;
            }

            case 6: {
                saveLatestGameSettings(player, currentCategory);
                cout << "Dziękuję za grę!" << endl;
                break;
            }

            default: {
                break;
            }
        }
    } while (menuChoice != 6);

    return 0;
}