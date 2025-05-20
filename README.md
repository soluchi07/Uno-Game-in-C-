# UNO C++ Console Game

This project is a simple console-based implementation of the classic card game UNO, written in C++. It allows multiple players to play UNO in a turn-based fashion, simulating the core mechanics of the game.

## Features

- Supports 4 players (can be extended)
- Implements standard UNO cards: numbers, skips, reverses, +2, wild, and wild +4
- Handles turn direction, stacking of +2 and +4 cards, and color changes
- Console-based user interaction for playing cards and making choices

## File Structure

- `uno.cpp`: Main implementation of the game logic, including classes for `Card`, `Deck`, `Player`, and `GameState`.
- `uno.h`: Header file with class declarations.
- `client.cpp`: (Optional) Entry point or additional client code for running the game.

## How to Build and Run

1. **Clone or download the repository.**
2. **Open a terminal in the project directory.**
3. **Compile the code:**
   ```sh
   g++ -std=c++11 uno.cpp client.cpp -o uno
   ```
   (You may need to adjust the command if you use a different compiler or file structure.)
4. **Run the game:**
   ```sh
   ./uno
   ```
   On Windows, use `uno.exe` instead of `./uno`.

## How to Play

- The game will prompt each player in turn to play a card or pick up from the deck.
- Follow the on-screen instructions to select cards and respond to special actions (e.g., color choice for wild cards).
- The game continues until a player has no cards left.

## Notes

- The game logic can be extended to support more players, advanced rules, or a graphical interface.
- This is a learning project and may not cover all edge cases of official UNO rules.

## License

This project is provided for educational purposes. No official affiliation with Mattel or the UNO brand.
