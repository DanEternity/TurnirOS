#pragma once
#include "globals.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>

/*
Данный модуль содержит все функции игры. 
*/

/*
int getTableCardCount(int pl);
	Возвращает количество карт на столе, принадлежащих выбранному игроку
	pl - индекс игрока. 0 или 1

void getAction(int &type, int &scr, int &dst, int &param, int &code);
	Функция получения команды от игрока
	type - код ID команды
	scr - 
	dst - 
	param -
	code -

void processAttack(int scr, int trg);
	Функция проведения атаки
	scr - выбранное существо 
	trg - цель атаки

void processDrawACard(int pl);
	Функция получения карты
	pl - индекс игрока, который должен получить карту

int getLeftTaunt(int pl);
	Функция возвращает индекс первого существа-провокации. -1 - означает, что провокаций нет.
	pl - индекс игрока, чьё существо атакуют

void processPlayCard(int card, int pos, int trg);
	Функция разыгрывания карты.
	card - индекс карты в руке
	pos - позиция для розыгрыша карты
	trg - цель карты (для заклинаний)

void destroyCard(int side, int pos);
	Функция уничтожения карты на столе
	side - индекс игрока
	pos - индекс карты на столе

void processTurnMain();
	Функция с основным циклом хода игрока

void loadDeck(string filename, int pl);
	Функция загрузки колоды игрока
	filename - название файла с колодой
	pl - индекс игрока
*/

int getTableCardCount(int pl);//Получить количество существ на столе у данного игрока
void getAction(int &type, int &scr, int &dst, int &param, int &code);//Считать запрос игрока
void processAttack(int scr, int trg);//Вызывается при получении команды на атаку
void processDrawACard(int pl);//Получение карты
int getLeftTaunt(int pl); // pl = игрок чьё существо атакует (соответственно провокация будет 1-pl). Возвращает количество оставшихся провокаций. -1 озгначает, что их нет.
void processPlayCard(int card, int pos, int trg);//Вызывается при разыгрывании карты
void destroyCard(int side, int pos);//Уничтожает карту
void processTurnMain();//Функция с основным циклом
void loadDeck(string filename, int pl);//Загружает колоду
void getTable(int pl);
void getHand(int pl);
void getInfo(int pl);
void shuffleDeck(int pl);