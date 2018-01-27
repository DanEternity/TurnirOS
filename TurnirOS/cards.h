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

	/* ��� ������ ��� ������� */
	/*
	1. void fName(); ��������� ����� ����� �� �������� (��� name ����� �����, ������� ���-�� ������)
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

	void fNone();
	void fBuffStats(); // add atr1 to atk // add atr2 to def // to @selected@ allied unit
	void fDamage(); // deal atr1 dmg to @selected@ enemy unit // DO NOT COMPLETED

};