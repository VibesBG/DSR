# Tournament Manager (C++)

A C++ console app for running a sports tournament: register players, search and sort them, save them to a file, and play out the bracket.

University coursework. The interface is in Bulgarian.

## Features

- Add up to 100 players (tournament number, world ranking, name, country, points, trophies)
- Show all players in a table, or only those from one country / with the fewest trophies
- Sort by world ranking or by trophies won
- Save players to and load them from a binary file (`players.bin`)
- Tournament mode: make the first-round pairings, enter scores, then build the knockout rounds

## Build

Windows only (uses `Windows.h` so Cyrillic shows correctly in the console).

```bash
g++ DSR.cpp -o tournament.exe
tournament.exe
```

Or open `DSR.cpp` in Visual Studio and run it.
