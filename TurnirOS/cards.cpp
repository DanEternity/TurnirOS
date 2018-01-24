#include "cards.h"
#include <algorithm>

Card::Card()
{
}

Card::Card(Card * q)
{
	memcpy(this, q, sizeof(Card));
}

Card::~Card()
{
}

void Card::playCard()
{
	if (!requredSp)
	{
		effPTR(); // CALL CARD ABILITY FUNCTION
	}
	else
	{
		// Something special requred for this card
	}
}

void Card::fNone()
{
	// Do nothing
}

void Card::fBuffStats()
{
	// atr1 = atk
	// atr2 = def
	table[player][selected]->Atk += atr1;
	table[player][selected]->maxAtk = max(table[player][selected]->Atk, table[player][selected]->maxAtk);
	table[player][selected]->Def += atr2;
	table[player][selected]->maxDef += atr2;
}

void Card::fDamage()
{
	// atr1 = dmg
	table[1-player][selected]->Def -= atr1;
}
