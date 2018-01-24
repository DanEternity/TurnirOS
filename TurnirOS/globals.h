#pragma once
#include <cards.h>
#include <vector>

using namespace std; 

class Card;

// Decks

extern vector<Card*> deck[2];


// Hands

extern vector<Card*> hand[2];

// info heroes

extern int health[2];

extern int mana[2];
extern int maxMana[2];

// info game

extern int turn; // номер хода
extern int player; // кто из игроков ходит

// info table

extern Card * table[2][7]; // pole
extern bool tableCheck[2][7]; // temp. unit exist true/false

extern int selected;
extern int target;

int qqq();