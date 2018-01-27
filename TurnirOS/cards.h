#pragma once
#include<globals.h>

class Card
{
public:
	Card();
	Card(Card * q);
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
	void (*effPTR)();

	bool isSpell; // IMPORTANT
	bool isStorm;
	bool isRush;
	bool isCurse;
	bool isTaunt;
	bool isTargetable; // IMPORTANT
	bool isCanAttack;
	bool isLastWord;

	// info
	bool requredSp;
	int atr1;
	int atr2;
	int atr3;

	void playCard();

	// Card abilities/fuctions

	/* Как писать эти функции */
	/*
	1. void fName(); Заголовок такой чтобы не путаться (где name любое слово, которое что-то значит)
	2. atr1 atr2 atr3 это параметры которые можно использовать в функциях (они настраиваются заранеее, при загрузки карт)
	3. tableCheck[player][target] хотя это бред, но лучше убедиться, что цель атаки существует
	особенно актуально, для эффектов бьющих по площади
	4. Комментарии... что значат например atr1, atr2, atr3 конкретно в вашей функции
	5. Функции имеют доступ table[][]  (игровое поле) и могут производить любые действия
	6. Если в процессе работы эффекта карты кто-то сдох, вы должны сделать refresh = true; иначе всё будет ОЧЕНЬ ПЛОХО
	7. Если эффект предполагает уничтожение существа, можно установить текущее (и максимальное) здоровье (def) на -999.
	(главное не забыть сделать refresh)
	8. Не выполняйте refresh просто так, это может повесить систему
	*/

	void fNone();
	void fBuffStats(); // add atr1 to atk // add atr2 to def // to @selected@ allied unit
	void fDamage(); // deal atr1 dmg to @selected@ enemy unit // DO NOT COMPLETED

};