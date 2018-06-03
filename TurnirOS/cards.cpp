#include "cards.h"

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
	isDisabled = q->isDisabled;
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
		// Скорее всего это работать не будет =)
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
	refresh = true;
	Qlog << player << " EFFECT " << "DAMAGE " << 1 - player << ' ' << selected << "  dmg " << scr->atr1 << endl;
}

void fManaUp(Card * scr)
{
	// Нужно создать событие, но у нас нет событий...
	mana[player] += scr->atr1; // Она может превысить значение 10.
	Qlog << player << " EFFECT " << "MANA+= " << scr->atr1 << endl;
	// Как видно не увеличивает максимальный показатель маны
}

void fFreeze(Card * scr)
{
	//table[1 - player][selected]->isCanAttack = false;
	table[1 - player][selected]->isDisabled = true;
	Qlog << player << " EFFECT " << "FREEZE " << 1 - player << ' ' << selected << endl;
}

void fLWCreateCreature(Card * scr)
{
	//

}

void fDrawCards(Card * scr)
{
	// atr1 = card count
	// atr2 = 0 for player, 1 for enemy

	Qlog << player << " EFFECT " << "DRAW_A_CARD " << scr->atr1 << endl;

	int pl;
	if (scr->atr2 == 0)
	{
		pl = player;
	}
	else
		pl = 1 - player;
	for (int i(0); i < scr->atr1; i++)
	{
		// Log?
		Qlog << pl << " DRAWCARD ";// << //endl;

									//

		if (deck[pl].size() == 0)
		{
			// Draw fatique (1.. 2.. 3.. 4.. и тд урона)

			fatique[pl]++;
			health[pl] -= fatique[pl];
			Qlog << "-1 FATIQUE " << fatique[pl] << endl;
		}
		else
		{
			if (hand[pl].size() == 9)
			{
				// log
				// discard card
				Qlog << deck[pl][0]->id << ' ' << deck[pl][0]->manaCost << ' ' << deck[pl][0]->Atk << ' ' << deck[pl][0]->Def << endl;
				delete deck[pl][0];

			}
			else
			{
				Qlog << deck[pl][0]->id << ' ' << deck[pl][0]->manaCost << ' ' << deck[pl][0]->Atk << ' ' << deck[pl][0]->Def << endl;
				hand[pl].push_back(deck[pl][0]);
			}
			deck[pl].erase(deck[pl].begin() + 0);

		}
	}

	
}

void fDamageAOE(Card * scr)
{
	// atr1 = dmg
	for (int i(0); i < 7; i++)
	{
		if (tableCheck[player][i] && table[player][i] != scr)
		{
			table[player][i]->Def -= scr->atr1;
			refresh = true;
			Qlog << player << " EFFECT " << "DAMAGE " << player << ' ' << i << "  dmg " << scr->atr1 << endl;
		}
		if (tableCheck[1-player][i])
		{
			table[1-player][i]->Def -= scr->atr1;
			refresh = true;
			Qlog << player << " EFFECT " << "DAMAGE " << 1-player << ' ' << i << "  dmg " << scr->atr1 << endl;
		}
	}
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
	t->isStorm = false;
	t->isRush = false;
	t->isCurse = false;
	t->isTaunt = false;
	t->isTargetable = false;
	t->isCanAttack = false;
	t->isLastWord = false;
	t->isDisabled = false;

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
	Card * t; // Эта переменная чисто для сокращения кода
	
	//Функция загружает все карты в базу данных
	
	AddCard("Coin", 0, 0, 0, "a");//Добавить монетку 
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

	// testing

	AddCard("ID 5", 3, 2, 2, "s");

	AddCard("ID 6", 4, 3, 4, "p");

	AddCard("ID 7", 5, 6, 5, "n");

	AddCard("ID 8", 4, 2, 1, "b");
	t = DataBase[DataBase.size() - 1];
	t->effPTR = fDrawCards;
	t->atr1 = 2;
	t->atr2 = 0;

	AddCard("ID 9", 2, 0, 0, "at");
	t = DataBase[DataBase.size() - 1];
	t->effPTR = fDamage;
	t->atr1 = 3;

	AddCard("ID 10", 7, 4, 4, "bp");
	t = DataBase[DataBase.size() - 1];
	t->effPTR = fDamageAOE;
	t->atr1 = 2;
}
