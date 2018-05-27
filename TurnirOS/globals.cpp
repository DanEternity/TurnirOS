#include "globals.h"


// Decks

vector<Card*> deck[2];


// Hands

vector<Card*> hand[2];

// info heroes

int health[2];

int mana[2];
int maxMana[2];

// info game

int turn; // номер хода
int player; // кто из игроков ходит

			// info table

Card * table[2][7]; // pole
bool tableCheck[2][7]; // temp. unit exist true/false

int selected;
int target;

bool refresh = false;
vector<Card*> DataBase;
int debugVal = 0;
ofstream Qlog("log.txt");
bool gameExit = false;

int qqq()
{
	return 0;
}
