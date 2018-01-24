#pragma once
#include <globals.h>
#include <algorithm>
/*
� ���� ������ ����� ����������� �������� � ����� ���� ������� ����.


*/
int getTableCardCount(int pl);

void getAction(int &type, int &scr, int &dst, int &param, int &code);

void processAttack(int scr, int trg);

void processDrawACard(int pl);

int getLeftTaunt(int pl); // pl = ����� ��� �������� ������� (�������������� ���������� ����� 1-pl)

void processPlayCard(int card, int pos, int trg);

void destroyCard(int side, int pos);

void processTurnMain();