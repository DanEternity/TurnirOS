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

	int effect;

	bool isStorm;
	bool isRush;
	bool isCurse;
	bool isTaunt;
	bool isTargetable;
	bool isCanAttack;


};