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
    //add conditions for wild cards
    //fix bugs with the direction variable
    //add conditions for stacking or double decking
    //automate players if this passes tests
    //create players that use diff strategies with dumb and smarter ones
    //add a way to say uno and get a penalty if you don't
    //add a way to customize the user's name
    
    Deck *main;
    GameState gameState;
    gameState.deck = main;
    gameState.deck->shuffleDeck();
    for (int i = 0; i < gameState.no_of_players; i++)
    {
        // Pick 7 cards from the deck
        for (int j = 0; j < 7; j++)
        {
            gameState.players[i].pickCard(gameState.deck->getCards()[0]);
            gameState.deck->getCards().erase(gameState.deck->getCards().begin());
        }
    }

    cout << "The first card is " << gameState.currentCard.colour << " " << gameState.currentCard.value << endl;

    // Main game loop
    while (!gameState.gameOver)
    {
        //find a way to shuffle the deck every couple of rounds
        Player &currentPlayer = gameState.players[gameState.currentPlayerIndex];
        cout << "Player " << gameState.currentPlayerIndex + gameState.direction << "'s turn." << endl;
        cout << "Do you want to play this round? (y/n)" << endl;
        char choice;
        cin >> choice;
        if (choice == 'y')
        {
            cout << "What card do you want to play? I'll show you your cards. Type the card's index." << endl;
            currentPlayer.seeHand();
            int index;
            cin >> index;

            // Check if the card is valid
            if (isValidCard(currentPlayer.hand[index], gameState.currentCard))
            {
                gameState.deck->getCards().push_back(gameState.currentCard);
                gameState.currentCard = currentPlayer.playCard(index);
                cout << "You played: " << gameState.currentCard.colour << " " << gameState.currentCard.value << endl;
                gameState.cardOutcome(gameState.currentCard);
            }
            else
            {
                cout << "Invalid card played. You lose your turn as a penalty" << endl;
            }
            
        }
        else
        {
            cout << "You don't want to play this round, so pick a card from the deck." << endl;
            currentPlayer.pickCard(gameState.deck->getCards()[0]);
            gameState.deck->getCards().erase(gameState.deck->getCards().begin());
        }

        // Check for game over condition
        if (currentPlayer.hand.empty())
        {
            cout << "Player " << gameState.currentPlayerIndex + 1 << " wins!" << endl;
            gameState.gameOver = true;
        }
        else
        {
            cout << "You have " << currentPlayer.hand.size() << " cards left." << endl;
        }
        // add way to say uno lest you get a penalty

        gameState.currentPlayerIndex = (gameState.currentPlayerIndex + gameState.direction) % gameState.players.size();

        cout << "Current card: " << gameState.currentCard.colour << " " << gameState.currentCard.value << endl;
    }

    cout << "Game over!" << endl;
    cout << "Thanks for playing!" << endl;
}