#pragma once
#include<globals.h>

class Card
{
public:
	Card();
	~Card();

	int scrManaCost;
	int scrAtk;
	int scrDef;

	int manaCost;
	int Atk; // Current Atk;
	int Def; // Current Def;

	int maxAtk;
	int maxDef;

	int effect; // ?

	bool isStorm;
	bool isRush;
	bool isCurse;
	bool isTaunt;
	bool isTargetable;
	bool isCanAttack;

	// info

	int atr1;
	int atr2;
	int atr3;

	// Card abilities/fuctions

	void fBuffStats(); // add atr1 to atk // add atr2 to def // to @selected@ card


};