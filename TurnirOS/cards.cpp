#include "cards.h"
#include <algorithm>

Card::Card()
{
}

Card::~Card()
{
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
