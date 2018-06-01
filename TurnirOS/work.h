#pragma once
#include "globals.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>

/*
������ ������ �������� ��� ������� ����. 
*/

/*
int getTableCardCount(int pl);
	���������� ���������� ���� �� �����, ������������� ���������� ������
	pl - ������ ������. 0 ��� 1

void getAction(int &type, int &scr, int &dst, int &param, int &code);
	������� ��������� ������� �� ������
	type - ��� ID �������
	scr - 
	dst - 
	param -
	code -

void processAttack(int scr, int trg);
	������� ���������� �����
	scr - ��������� �������� 
	trg - ���� �����

void processDrawACard(int pl);
	������� ��������� �����
	pl - ������ ������, ������� ������ �������� �����

int getLeftTaunt(int pl);
	������� ���������� ������ ������� ��������-����������. -1 - ��������, ��� ���������� ���.
	pl - ������ ������, ��� �������� �������

void processPlayCard(int card, int pos, int trg);
	������� ������������ �����.
	card - ������ ����� � ����
	pos - ������� ��� ��������� �����
	trg - ���� ����� (��� ����������)

void destroyCard(int side, int pos);
	������� ����������� ����� �� �����
	side - ������ ������
	pos - ������ ����� �� �����

void processTurnMain();
	������� � �������� ������ ���� ������

void loadDeck(string filename, int pl);
	������� �������� ������ ������
	filename - �������� ����� � �������
	pl - ������ ������
*/

int getTableCardCount(int pl);//�������� ���������� ������� �� ����� � ������� ������
void getAction(int &type, int &scr, int &dst, int &param, int &code);//������� ������ ������
void processAttack(int scr, int trg);//���������� ��� ��������� ������� �� �����
void processDrawACard(int pl);//��������� �����
int getLeftTaunt(int pl); // pl = ����� ��� �������� ������� (�������������� ���������� ����� 1-pl). ���������� ���������� ���������� ����������. -1 ���������, ��� �� ���.
void processPlayCard(int card, int pos, int trg);//���������� ��� ������������ �����
void destroyCard(int side, int pos);//���������� �����
void processTurnMain();//������� � �������� ������
void loadDeck(string filename, int pl);//��������� ������
void getTable(int pl);
void getHand(int pl);
void getInfo(int pl);
void shuffleDeck(int pl);