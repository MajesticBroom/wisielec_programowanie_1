# Wisielec w Terminalu
Politechnika Śląska
<br/>
Wydział Matematyki Stosowanej
<br/>
Kierunek Informatyka


Projekt zaliczeniowy z przedmiotu "Programowanie I".

## 1. Opis projektu.
**"Wisielec w Terminalu"** to aplikacja konsolowa
zaimplementowana w języku C++ zgodnie z paragydmatem
programowania proceduralnego.
Projekt stanowi rozbudowaną wariację klasycznej gry logicznej,
wprowadzając element rywalizacji pomiędzy graczem a komputerem,
w formie wyścigu.

Program został zaprojektowany i przetestowany za pomocą następujących narzędzi:
- środowisko CLION
- kompilator clang
- system operacyjny macOS

Interfejs użytkownika opiera się na trybie tekstowym (CLI)
z wykorzystaniem kodów sterujących ANSI do formatowania
i kolorowania tekstu konsoli.


## 2. Funkcjonalności
**Tryb rywalizacji** - mechanika wyścigu,
w którym użytkownik i komputer równolegle odgadują to samo hasło.
System zarządza turami obu stron niezależnie.

**Dwutorowy system zgadywania** - możliwość odgadnięcia w danej turze
pojedynczej litery lub podjęcia ryzyka odgadnięcia całego hasła,
za co przydzielane są dodatkowe punkty w przypadku prawidłowego strzału
lub kary za błędne odgadnięcie hasła.

**Algorytm przeciwnika (AI)** - symulacja inteligentnego gracza komputerowego,
który losuje litery, zapamiętuje swoje ruchy
i nigdy nie typuje dwukrotnie tej samej litery.

**Dynamiczna wizualizacja stanu gry** – graficzna reprezentacja postępu
za pomocą kolorowych napisów (dzięki kodom ANSI)
i grafik utworzonych za pomocą symboli ASCII w terminalu,
zmieniająca się wraz z utratą żyć (12 etapów rysowania szubienicy).

**System obsługi kategorii tematycznych** – dynamiczne wczytywanie
bazy haseł z zewnętrznych plików tekstowych,
umożliwiające łatwą rozbudowę gry o nowe słowa
bez ingerencji w kod źródłowy.
Rozgrywka w poszczególnej kategorii zależy od wyboru
użytkownika w menu głównym.

**Trwałość danych** – system zapisu i odczytu danych z plików,
obejmujący przechowywanie tablicy wyników
oraz historii ostatniej rozgrywki.

**Walidacja danych wejściowych** – zaawansowany mechanizm sprawdzania poprawności wprowadzanych
przez użytkownika danych – blokada znaków specjalnych, cyfr, ciągów znaków.

**Zarządzanie profilem gracza** – możliwość zmiany nicku,
wraz ze śledzeniem statystyk poszczególnych graczy
na tablicy wyników – funkcjonalność na wzór automatów z retro grami Arcade,
np.
```
Gracz 1 --------- 120pkt
Gracz 2 --------- 105pkt
```

## 3. Przebieg realizacji

### Wykorzystane biblioteki standardowe
|     Biblioteka    |              Kluczowe elementy              |                               Zastosowanie w projekcie                               |
|:-----------------:|:-------------------------------------------:|:------------------------------------------------------------------------------------:|
|     `<random>`    | std::mt19937, std::uniform_int_distribution | Zaawansowane generowanie liczb pseudolosowych dla ruchów komputera oraz wyboru słów. |
| `<unordered_set>` |           std::unordered_set<char>          |                     Przechowywanie użytych w trakcie rundy liter.                    |
|     `<vector>`    |                 std::vector                 |     Dynamiczne przechowywanie listy wyników, oraz list słów wczytanych z plików.     |
|    `<fstream>`    |         std::ifstream, std::ofstream        |                                 Operacje na plikach.                                 |
|     `<string>`    |                 std::string                 |          Manipulacja łańcuchami znaków, przechowywanie haseł i nazw graczy.          |
|    `<iostream>`   |             std::cin, std::cout             |                   Standardowa obsługa wejścia/wyjścia w Terminalu.                   |


### Struktura danych

Dane w programie są organizowane za pomocą struktur zdefiniowanych w pliku `models.h`:
- `struct Player`: Reprezentuje stan gracza (lub komputera) w trakcie bieżącej rozgrywki.
    - `std::string nickname`: Nazwa gracza.
    - `std::unordered_set<char> usedLetters`: Zbiór użytych przez gracza (lub komputer) liter, pozwalający na szybkie sprawdzanie duplikatów.
    - Zmienne całkowite (`int`):
      - `correctlyGuessedLetters`: Postęp zgadywania.
      - `livesLeft`: Pozostałe życia.
      - `points`: Punkty w danej rundzie.
      - `matchesPlayed`: Suma rozegranych rund.
      - `matchesWon`: Suma wygranych rund.
      - `totalPoints`: Suma punktów.
- `struct PlayerStats`: Służy do wczytywania i zapisywania statystyk globalnych.
- `struct Keyword`: Przechowuje informacje o aktualnym haśle.
  - `std::string word`: Treść hasła.
  - `int length`: Liczba liter w haśle.

