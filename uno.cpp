using namespace std;
#include <string>
#include <vector>
#include "uno.h"
#include <algorithm>
#include <random>
#include <iostream>
#include <cstdlib>
// look up <ctime> for random seed

GameState::GameState()
{
    deck = new Deck();
    direction = 1; // 1 for clockwise, -1 for counterclockwise
    no_of_players = 4;
    currentPlayerIndex = 0;
    gameOver = false;
    twoStack = 0;
    fourStack = 0;
    vector<Player> players = {};
    int starter = rand() % deck->getCards().size();

    currentCard = deck->getCards()[starter];
    for (int i = 0; i < no_of_players; i++)
    {
        players.push_back(Player());
    }
}

Card::Card() : value(""), colour("") {}
Card::Card(string v, string c) : value(v), colour(c) {}

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

Deck::Deck(vector<Card> c) : cards(c) {}

vector<Card>& Deck::getCards()
{
    return cards;
}

void Deck::shuffleDeck()
{
    random_device rd;
    mt19937 gen(rd());
    shuffle(cards.begin(), cards.end(), gen);
}

Player::Player()
{
    hand = {};
}

Card Player::playCard(int index)
{
    Card played = hand[index];
    hand.erase(hand.begin() + index);
    return played;
}

void Player::seeHand()
{
    cout << "Here's your hand:" << endl;
    for (int i = 0; i < hand.size(); i++)
    {
        cout << i << ": " << hand[i].colour << " " << hand[i].value << endl;
    }
}

void Player::pickCard(Card c)
{
    hand.push_back(c);
    cout << "You have picked up" << c.colour << " " << c.value << endl;
}

void GameState::pick4()
{
    fourStack++;
    char choice;
    cout << "Player " << currentPlayerIndex + 1 << " wants player " << currentPlayerIndex + 2 << " to pick four cards" << endl;
    cout << "Dpes Player " << currentPlayerIndex + 2 << " have a counter>?" << endl;
    cin >> choice;
    if (choice == 'y')
    {
        cout << "Player " << currentPlayerIndex + 2 << " has a counter" << endl;
        cout << "Player " << currentPlayerIndex + 2 << " plays the counter" << endl;
        fourStack = 0;
    }
    else
    {
        cout << "Player " << currentPlayerIndex + 2 << " does not have a counter" << endl;
        cout << "Player " << currentPlayerIndex + 2 << " picks up the cards" << endl;
        for (int i = 0; i < 4*fourStack; i++)
        // use i < (2*twoStack) + (4*fourStack) for functionality that allows for +2s to be countered by +4s
        {
            Card c = deck->getCards()[0];
            players[currentPlayerIndex + 2].pickCard(c);
            deck->getCards().erase(deck->getCards().begin());
        }
        
    }
}

void GameState::pick2()
{
    twoStack++;
    char choice;
    cout <<"Player " << currentPlayerIndex + 1 << " wants player " << currentPlayerIndex + 2 << " to pick two cards" << endl;
    cout << "Dpes Player " << currentPlayerIndex + 2 << " have a counter>?" << endl;
    cin >> choice;
    if (choice == 'y')
    {
        cout << "Player " << currentPlayerIndex + 2 << " has a counter" << endl;
        cout << "Player " << currentPlayerIndex + 2 << " plays the counter" << endl;
        twoStack = 0;
    }
    else
    {
        cout << "Player " << currentPlayerIndex + 2 << " does not have a counter" << endl;
        cout << "Player " << currentPlayerIndex + 2 << " picks up the cards" << endl;
        for (int i = 0; i < 2*twoStack; i++)
        // use i < (2*twoStack) + (4*fourStack) for functionality that allows for +2s to be countered by +4s
        {
            Card c = deck->getCards()[0];
            players[currentPlayerIndex + 2].pickCard(c);
            deck->getCards().erase(deck->getCards().begin());
        }
        
    }
    
}

bool isValidCard(Card c, Card current)
{
    // c is Player.hand[index]
    if (c.value == current.value || c.colour == current.colour || c.colour == "all" || current.colour == "all")
    {
        return true;
    }
    else
    {
        return false;
    }//add conditions for wild cards
}

// Add any additional functions or classes as needed
void GameState::cardOutcome(Card c)
{
    
    if (currentCard.value == "skip")
    {
        currentPlayerIndex = currentPlayerIndex + direction;
    }
    else if (currentCard.value == "reverse")
    {
        direction *= -1;
    }
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
    else if (currentCard.value == "+2")
    {
        cout << "Player " << currentPlayerIndex + 1 << " plays a +2 card." << endl;
        pick2();
    }
}