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
	void (*effPTR)(Card * scr);//��������� �� ������� �������

	string spec;//������ �������������� �����
	//����� ������������ �����
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
	bool requredSp;//���� �� �������������� ����������� �����, ������� ����������� ��� ���������
	int atr1;
	int atr2;
	int atr3;

	void playCard();//��������� �����
	void updStats();//�������� ��������������
};

void AddCard(string name, int mana, int atk, int def, string spec);//�������� �����
void LoadCards();//��������� �����

// Card abilities/fuctions

/* ��� ������ ��� ������� */
/*
1. void fName(Card * scr); ��������� ����� ����� �� �������� (��� name ����� �����, ������� ���-�� ������)
2. atr1 atr2 atr3 ��� ��������� ������� ����� ������������ � �������� (��� ������������� ��������, ��� �������� ����)
3. tableCheck[player][target] ���� ��� ����, �� ����� ���������, ��� ���� ����� ����������
�������� ���������, ��� �������� ������ �� �������
4. �����������... ��� ������ �������� atr1, atr2, atr3 ��������� � ����� �������
5. ������� ����� ������ table[][]  (������� ����) � ����� ����������� ����� ��������
6. ���� � �������� ������ ������� ����� ���-�� ����, �� ������ ������� refresh = true; ����� �� ����� ����� �����
7. ���� ������ ������������ ����������� ��������, ����� ���������� ������� (� ������������) �������� (def) �� -999.
(������� �� ������ ������� refresh)
8. �� ���������� refresh ������ ���, ��� ����� �������� �������
*/

void fNone(Card * scr);
void fBuffStats(Card * scr); // add atr1 to atk // add atr2 to def // to @selected@ allied unit
void fDamage(Card * scr); // deal atr1 dmg to @selected@ enemy unit // DO NOT COMPLETED
void fManaUp(Card * scr); // Give atr1 mana until the end of the turn
void fFreeze(Card * scr); // Freeze enemy; He will lost his next turn
void fLWCreateCreature(Card * scr); // Create creature with ID = atr1
void fDrawCards(Card * scr);
void fDamageAOE(Card * scr); // deal dmg to all except this card;