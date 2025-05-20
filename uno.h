#ifndef HEADER_FILE_NAME_H
#define HEADER_FILE_NAME_H
using namespace std;
#include <string>
#include <vector>

// Include necessary headers

// Define macros and constants

// Define class/struct/union

struct Card
{
    string value;
    string colour;

    Card(string v, string c);
    Card();
};

class Deck
{
private:
    vector<Card> cards;

public:
    void shuffleDeck();
    Deck();
    Deck(vector<Card> c);
    vector<Card>& getCards();
};

struct Player
{
    vector<Card> hand;

    Player();
    Card playCard(int index);
    void pickCard(Card c);
    void seeHand();
};

struct GameState
{
    Deck *deck;
    vector<Player> players;
    int direction; // 1 for clockwise, -1 for counterclockwise
    int twoStack;
    int fourStack;
    Card currentCard;
    int currentPlayerIndex;
    bool gameOver;
    int no_of_players;
    GameState();
    void cardOutcome(Card c);
    void pick2();
    void pick4();
};

bool isValidCard(Card c, Card current);

// Define function prototypes

#endif // HEADER_FILE_NAME_H