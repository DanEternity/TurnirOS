#include "cards.h"
#include <algorithm>

Card::Card()
{
}

Card::Card(Card * q)
{
	//memcpy(this, q, sizeof(Card));
	//effPTR = NULL;
	id = q->id;
	name = q->name;
	scrManaCost = q->scrManaCost;
	scrAtk = q->scrAtk;
	scrDef = q->scrDef;
	
	manaCost = q->manaCost;
	Atk = q->Atk;
	Def = q->Def;

	maxAtk = q->maxAtk;
	maxDef = q->maxDef;

	effect = q->effect;
	effPTR = q->effPTR;

	spec = q->spec;
	isSpell = q->isSpell;
	isStorm = q->isStorm;
	isRush = q->isRush;
	isCurse = q->isCurse;
	isTaunt = q->isTaunt;
	isTargetable = q->isTargetable;
	isCanAttack = q->isCanAttack;
	isLastWord = q->isLastWord;
	isFanfare = q->isFanfare;
	isClash = q->isClash;

	requredSp = q->requredSp;
	atr1 = q->atr1;
	atr2 = q->atr2;
	atr3 = q->atr3;
}

Card::~Card()
{
}

void Card::playCard()
{
	if (!requredSp)
	{
		// —корее всего это работать не будет =)
		effPTR(this); // CALL CARD ABILITY FUNCTION
	}
	else
	{
		// Something special requred for this card
	}
}

void Card::updStats()
{
	manaCost = scrManaCost;
	Atk = scrAtk;
	Def = scrDef;
	maxAtk = Atk;
	maxDef = Def;
}

void fNone(Card * scr)
{
	// Do nothing
}

void fBuffStats(Card * scr)
{
	// atr1 = atk
	// atr2 = def
	table[player][selected]->Atk += scr->atr1;
	table[player][selected]->maxAtk = max(table[player][selected]->Atk, table[player][selected]->maxAtk);
	table[player][selected]->Def += scr->atr2;
	table[player][selected]->maxDef += scr->atr2;
}

void fDamage(Card * scr)
{
	// atr1 = dmg
	table[1-player][selected]->Def -= scr->atr1;
}

void fManaUp(Card * scr)
{
	// Ќужно создать событие, но у нас нет событий...
	mana[player] += scr->atr1; // ќна может превысить значение 10.
	//  ак видно не увеличивает максимальный показатель маны
}

void fFreeze(Card * scr)
{
	table[1 - player][selected]->isCanAttack = false;
}

void fLWCreateCreature(Card * scr)
{
	//
}



void AddCard(string name, int mana, int atk, int def, string spec)
{
	DataBase.push_back(new Card());
	int q = DataBase.size() - 1;
	Card * t = DataBase[q];
	t->name = name;
	t->scrManaCost = mana;
	t->scrAtk = atk;
	t->scrDef = def;
	t->spec = spec;
	t->effPTR = fNone;
	t->id = q;

	t->isSpell = false;
	t->isStorm = false;;
	t->isRush = false;
	t->isCurse = false;
	t->isTaunt = false;
	t->isTargetable = false;
	t->isCanAttack = false;
	t->isLastWord = false;

	for (int i(0); i < spec.size(); i++)
	{
		switch (spec[i])
		{
		case 'a': t->isSpell = true; break;
		case 'p': t->isTaunt = true; break;
		case 'b': t->isFanfare = true; break;
		case 't': t->isTargetable = true; break;
		case 'd': t->isLastWord = true; break;
		case 'x': t->isCurse = true; break;
		case 'r': t->isRush = true; break;
		case 's': t->isStorm = true; break;
		case 'c': t->isClash = true; break;
		default:
			break;
		}
	}
}

void LoadCards()
{
	Card * t; // Ёта переменна€ чисто дл€ сокращени€ кода
	/* ‘ункци€ загружает все карты в базу данных*/
	
	AddCard("Coin", 0, 0, 0, "a"); 
	t = DataBase[DataBase.size() - 1];
	t->atr1 = 1;
	t->effPTR = fManaUp;

	AddCard("ID 1", 1, 0, 2, "p");

	AddCard("ID 2", 1, 1, 2, "n");

	AddCard("ID 3", 1, 1, 1, "bt");
	t = DataBase[DataBase.size() - 1];
	t->effPTR = fFreeze;

	AddCard("ID 4", 1, 1, 1, "d");
	t = DataBase[DataBase.size() - 1];
//	t->effPTR = f; // Not finished;



}
