#pragma once
#include <globals.h>
#include <algorithm>
/*
В этом модуле будет происходить проверка и вызов всех функций игры.


*/
int getTableCardCount(int pl);

void getAction(int &type, int &scr, int &dst, int &param, int &code);

void processAttack(int scr, int trg);

void processDrawACard(int pl);

int getLeftTaunt(int pl); // pl = игрок чьё существо атакует (соответственно провокация будет 1-pl)

void processPlayCard(int card, int pos, int trg);

void destroyCard(int side, int pos);

void processTurnMain();