using namespace std;
#include <string>
#include <vector>
#include "uno.h"
#include <algorithm>
#include <random>
#include <iostream>
#include <cstdlib>
// look up <ctime> for random seed

// ------------------- GAMESTATE CONSTRUCTOR -------------------
// Initializes the deck, sets direction, player count, and other game state variables.
// Randomly selects a starting card and creates player objects.
GameState::GameState()
{
    deck = new Deck();
    direction = 1; // 1 for clockwise, -1 for counterclockwise
    no_of_players = 4;
    currentPlayerIndex = 0;
    gameOver = false;
    twoStack = 0;
    fourStack = 0;
    players = {};
    int starter = rand() % deck->getCards().size();

    currentCard = deck->getCards()[starter];
    for (int i = 0; i < no_of_players; i++)
    {
        players.push_back(Player());
    }
}

// ------------------- CARD CLASS -------------------
// Default and parameterized constructors for Card objects.
Card::Card() : value(""), colour("") {}
Card::Card(string v, string c) : value(v), colour(c) {}

// ------------------- DECK CLASS -------------------
// Default constructor creates all UNO cards and adds them to the deck.
Deck::Deck()
{
    cards = {};
    int i = 0;
    while (i < 9)
    {
        cards.push_back(Card(to_string(i + 1), "red"));
        cards.push_back(Card(to_string(i + 1), "blue"));
        cards.push_back(Card(to_string(i + 1), "green"));
        cards.push_back(Card(to_string(i + 1), "yellow"));
        cards.push_back(Card(to_string(i + 1), "red"));
        cards.push_back(Card(to_string(i + 1), "blue"));
        cards.push_back(Card(to_string(i + 1), "green"));
        cards.push_back(Card(to_string(i + 1), "yellow"));
        i++;
    }
    // Add special cards: skip, reverse, +2, wild, wild +4, and 0s
    cards.push_back(Card("skip", "red"));
    cards.push_back(Card("skip", "blue"));
    cards.push_back(Card("skip", "green"));
    cards.push_back(Card("skip", "yellow"));
    cards.push_back(Card("skip", "red"));
    cards.push_back(Card("skip", "blue"));
    cards.push_back(Card("skip", "green"));
    cards.push_back(Card("skip", "yellow"));
    cards.push_back(Card("reverse", "red"));
    cards.push_back(Card("reverse", "blue"));
    cards.push_back(Card("reverse", "green"));
    cards.push_back(Card("reverse", "yellow"));
    cards.push_back(Card("reverse", "red"));
    cards.push_back(Card("reverse", "blue"));
    cards.push_back(Card("reverse", "green"));
    cards.push_back(Card("reverse", "yellow"));
    cards.push_back(Card("+2", "red"));
    cards.push_back(Card("+2", "blue"));
    cards.push_back(Card("+2", "green"));
    cards.push_back(Card("+2", "yellow"));
    cards.push_back(Card("+2", "red"));
    cards.push_back(Card("+2", "blue"));
    cards.push_back(Card("+2", "green"));
    cards.push_back(Card("+2", "yellow"));
    cards.push_back(Card("0", "red"));
    cards.push_back(Card("0", "blue"));
    cards.push_back(Card("0", "green"));
    cards.push_back(Card("0", "yellow"));
    i = 0;
    while (i < 4)
    {
        cards.push_back(Card("wild", "all"));
        cards.push_back(Card("wild +4", "all"));
        i++;
    }
}

// Alternate constructor for Deck that takes a vector of cards.
Deck::Deck(vector<Card> c) : cards(c) {}

// Returns a reference to the deck's card vector.
vector<Card> &Deck::getCards()
{
    return cards;
}

// Shuffles the deck using a random number generator.
void Deck::shuffleDeck()
{
    random_device rd;
    mt19937 gen(rd());
    shuffle(cards.begin(), cards.end(), gen);
}

// ------------------- PLAYER CLASS -------------------
// Default constructor initializes an empty hand.
Player::Player()
{
    hand = {};
}

// Removes and returns the card at the given index from the player's hand.
Card Player::playCard(int index)
{
    Card played = hand[index];
    hand.erase(hand.begin() + index);
    return played;
}

// Prints the player's hand to the console.
void Player::seeHand()
{
    cout << "Here's your hand:" << endl;
    for (int i = 0; i < hand.size(); i++)
    {
        cout << i << ": " << hand[i].colour << " " << hand[i].value << endl;
    }
}

// Adds a card to the player's hand and prints a message.
void Player::pickCard(Card c)
{
    hand.push_back(c);
    cout << "You have picked up " << c.colour << " " << c.value << endl;
}

// ------------------- GAMESTATE SPECIAL CARD HANDLING -------------------

// Handles the effect of a wild +4 card, including stacking and counters.
void GameState::pick4()
{
    // Increment the +4 stack and determine the next player.
    fourStack++;
    char choice;
    int nextIndex = (currentPlayerIndex + fourStack + direction) % no_of_players;

    // Ask if the next player has a counter.
    cout << "Player " << (currentPlayerIndex + fourStack) % no_of_players << " plays a wild +4 card." << endl;
    cout << "Does Player " << nextIndex << " have a counter? (y/n)" << endl;
    cin >> choice;
    if (choice == 'y')
    {
        // If countered, recursively call pick4 for stacking.
        cout << "Player " << nextIndex << " has a counter" << endl;
        cout << "Player " << nextIndex << " plays the counter" << endl;
        pick4();
        // For now, only another +4 is a valid counter.
    }
    else
    {
        // If not countered, next player picks up the stacked cards.
        cout << "Player " << nextIndex << " does not have a counter" << endl;
        cout << "Player " << nextIndex << " picks up the cards" << endl;
        for (int i = 0; i < 4 * fourStack; i++)
        {
            if (deck->getCards().empty())
            {
                cout << "Deck is empty! Cannot pick more cards." << endl;
                break;
            }
            Card c = deck->getCards()[0];
            players[nextIndex - 1].pickCard(c);
            deck->getCards().erase(deck->getCards().begin());
        }
    }
    fourStack = 0;
    currentPlayerIndex = currentPlayerIndex + direction;
}

// Handles the effect of a +2 card, including stacking and counters.
void GameState::pick2()
{
    // Increment the +2 stack and determine the next player.
    twoStack++;
    char choice;
    int nextIndex = (currentPlayerIndex + twoStack + direction) % no_of_players;
    cout << "Player " << (currentPlayerIndex + twoStack) % no_of_players << " plays a +2 card." << endl;
    cout << "Does Player " << nextIndex << " have a counter? (y/n)" << endl;
    cin >> choice;
    if (choice == 'y')
    {
        // If countered, recursively call pick2 for stacking.
        cout << "Player " << nextIndex << " has a counter" << endl;
        cout << "Player " << nextIndex << " plays the counter" << endl;
        pick2();
        // For now, only another +2 is a valid counter.
    }
    else
    {
        // If not countered, next player picks up the stacked cards.
        cout << "Player " << nextIndex << " does not have a counter" << endl;
        cout << "Player " << nextIndex << " picks up the cards" << endl;
        for (int i = 0; i < 2 * twoStack; i++)
        {
            if (deck->getCards().empty())
            {
                cout << "Deck is empty! Cannot pick more cards." << endl;
                break;
            }
            Card c = deck->getCards()[0];
            players[nextIndex - 1].pickCard(c);
            deck->getCards().erase(deck->getCards().begin());
        }
    }
    twoStack = 0;
    currentPlayerIndex = currentPlayerIndex + direction;
}

// ------------------- CARD VALIDATION -------------------
// Checks if a card can be played on top of the current card.
bool isValidCard(Card c, Card current)
{
    // Card is valid if it matches value, colour, or is a wild card.
    if (c.value == current.value || c.colour == current.colour || c.colour == "all")
    {
        return true;
    }
    else
    {
        return false;
    }
    // Additional conditions for wild cards can be added here.
}

// ------------------- CARD OUTCOME HANDLER -------------------
// Handles the effects of special cards after they are played.
void GameState::cardOutcome(Card c)
{
    // If skip is played, advance to the next player.
    if (currentCard.value == "skip")
    {
        currentPlayerIndex = currentPlayerIndex + direction;
    }
    // If reverse is played, change the direction of play.
    else if (currentCard.value == "reverse")
    {
        direction *= -1;
    }
    // If wild is played, prompt the player to choose a colour.
    else if (currentCard.value == "wild")
    {
        cout << "Player " << currentPlayerIndex + 1 << " plays a wild card. What colour do you want to play? (use lowercase)" << endl;
        string colour;
        cin >> colour;
        while (colour != "red" && colour != "blue" && colour != "green" && colour != "yellow")
        {
            cout << "Invalid colour. Please choose red, blue, green, or yellow." << endl;
            cin >> colour;
        }
        currentCard.colour = colour;
    }
    // If wild +4 is played, prompt for colour and handle penalty.
    else if (currentCard.value == "wild +4")
    {
        cout << "Player " << currentPlayerIndex + 1 << " plays a wild +4 card. What colour do you want to play? (use lowercase)" << endl;
        string colour;
        cin >> colour;
        while (colour != "red" && colour != "blue" && colour != "green" && colour != "yellow")
        {
            cout << "Invalid colour. Please choose red, blue, green, or yellow." << endl;
            cin >> colour;
        }
        currentCard.colour = colour;
        pick4();
    }
    // If +2 is played, handle penalty.
    else if (currentCard.value == "+2")
    {
        pick2();
    }
}