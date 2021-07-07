#pragma once

#include "globals.h"
#include <string>
#include <vector>
#include <algorithm>

using std::string;

class Card
{
public:
	Card();
	Card(Card * q);
	~Card();

	int id;
	string name;

	int scrManaCost;
	int scrAtk;
	int scrDef;

	int manaCost;
	int Atk; // Current Atk;
	int Def; // Current Def;

	int maxAtk;
	int maxDef;

	int effect; // ?
	void (*effPTR)(Card * scr);//Указатель на йункцию эффекта

	string spec;//Строка спецификаторов карты
	//Флаги особенностей карты
	bool isSpell; // IMPORTANT
	bool isStorm;
	bool isRush;
	bool isCurse;
	bool isTaunt;
	bool isTargetable; // IMPORTANT
	bool isCanAttack;
	bool isLastWord;
	bool isFanfare;
	bool isClash;
	bool isDisabled; // CANT ATTACK // REMOVES AT THE END OF CARD TURN

	// info
	bool requredSp;//Есть ли дополнительные особенности карты, которые проявляются при розыгрыше
	int atr1;
	int atr2;
	int atr3;

	void playCard();//Разыграть карту
	void updStats();//Обновить характеристики
};

void AddCard(string name, int mana, int atk, int def, string spec);//Добавить карту
void LoadCards();//Загрузить карты

// Card abilities/fuctions

/* Как писать эти функции */
/*
1. void fName(Card * scr); Заголовок такой чтобы не путаться (где name любое слово, которое что-то значит)
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

void fNone(Card * scr);
void fBuffStats(Card * scr); // add atr1 to atk // add atr2 to def // to @selected@ allied unit
void fDamage(Card * scr); // deal atr1 dmg to @selected@ enemy unit // DO NOT COMPLETED
void fManaUp(Card * scr); // Give atr1 mana until the end of the turn
void fFreeze(Card * scr); // Freeze enemy; He will lost his next turn
void fLWCreateCreature(Card * scr); // Create creature with ID = atr1
void fDrawCards(Card * scr);
void fDamageAOE(Card * scr); // deal dmg to all except this card;