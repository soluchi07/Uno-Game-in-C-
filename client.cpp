using namespace std;
#include <string>
#include <vector>
#include "uno.h"
#include <algorithm>
#include <random>
#include <iostream>
#include <cstdlib>

int main()
{
    // ------------------- SETUP & INITIALIZATION -------------------
    // (Suggestions for future features are listed above)

    GameState gameState;           // Create the game state, which sets up the deck and players
    gameState.deck->shuffleDeck(); // Shuffle the deck at the start

    // Deal 5 cards to each player
    for (int i = 0; i < gameState.no_of_players; i++)
    {
        cout << "Player " << i + 1 << " picks a card from the deck." << endl
             << endl;
        for (int j = 0; j < 5; j++)
        {
            gameState.players[i].pickCard(gameState.deck->getCards()[0]);
            gameState.deck->getCards().erase(gameState.deck->getCards().begin());
        }
        cout << endl;
    }

    // Show the first card to start the game
    cout << "The first card is " << gameState.currentCard.colour << " " << gameState.currentCard.value << endl;

    // ------------------- MAIN GAME LOOP -------------------
    while (!gameState.gameOver)
    {
        // Get the current player for this turn
        Player &currentPlayer = gameState.players[gameState.currentPlayerIndex];
        cout << "Player " << gameState.currentPlayerIndex + 1 << "'s turn." << endl;

        // Ask if the player wants to play this round
        cout << "Do you want to play this round? (y/n)" << endl;
        char choice;
        cin >> choice;

        if (choice == 'y')
        {
            // Show the player's hand and ask which card to play
            cout << "What card do you want to play? I'll show you your cards. Type the card's index." << endl;
            currentPlayer.seeHand();
            int index;
            cin >> index;

            // Check if the selected card is valid to play
            if (isValidCard(currentPlayer.hand[index], gameState.currentCard))
            {
                // Place the current card back into the deck (as discard pile)
                gameState.deck->getCards().push_back(gameState.currentCard);
                // Play the selected card and update the current card
                gameState.currentCard = currentPlayer.playCard(index);
                cout << "You played: " << gameState.currentCard.colour << " " << gameState.currentCard.value << endl;
                // Handle the outcome of the played card (special actions, etc.)
                gameState.cardOutcome(gameState.currentCard);
            }
            else
            {
                // If the card is invalid, penalize the player by skipping their turn
                cout << "Invalid card played. You lose your turn as a penalty" << endl;
            }
        }
        else
        {
            // If the player chooses not to play, they must pick a card from the deck
            cout << "You don't want to play this round, so pick a card from the deck." << endl;
            currentPlayer.pickCard(gameState.deck->getCards()[0]);
            gameState.deck->getCards().erase(gameState.deck->getCards().begin());
        }

        // ------------------- GAME OVER CHECK -------------------
        // If the current player has no cards left, they win
        if (currentPlayer.hand.empty())
        {
            cout << "Player " << gameState.currentPlayerIndex + 1 << " wins!" << endl;
            gameState.gameOver = true;
        }
        else
        {
            // Otherwise, show how many cards the player has left
            cout << "You have " << currentPlayer.hand.size() << " cards left." << endl;
        }
        // (UNO call/penalty feature can be added here)

        // ------------------- ADVANCE TO NEXT PLAYER -------------------
        // If the direction is reversed and we're at the start, wrap to the last player
        if (gameState.direction == -1 && gameState.currentPlayerIndex == 0)
        {
            gameState.currentPlayerIndex = gameState.no_of_players - 1;
        }
        else
        {
            // Otherwise, move to the next player (handles both directions)
            gameState.currentPlayerIndex = (gameState.currentPlayerIndex + gameState.direction) % gameState.players.size();
        }

        // Show the current card at the end of the turn
        cout << "Current card: " << gameState.currentCard.colour << " " << gameState.currentCard.value << endl
             << endl;
    }

    // ------------------- GAME END -------------------
    cout << "Game over!" << endl;
    cout << "Thanks for playing!" << endl;
}