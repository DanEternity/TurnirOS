#include<iostream>
#include<cmath>
#include<algorithm>
#include<vector>
#include"globals.h"
#include"cards.h"
#include"work.h"

using namespace std;

const bool debugMode = true;

void initAll()
{
	const bool debugMode = true;

	// 
	// initialization
	//

	mana[0] = 0;
	mana[1] = 0;
	maxMana[1] = 0;
	health[1] = 30;

	//Установим текущий ход как первый
	turn = 0;

	//Обнулим поле
	for (int i(0); i < 2; i++)
		for (int j(0); j < 7; j++)
			tableCheck[i][j] = false;
}

void createPlayers()
{
	ifstream input;
	input.open("testProg.txt");
	string name1, name2;
	
	input >> name1 >> name2;
	//RunProcess(name1, )
	//RunProcess(name2, );
}

int main()
{
	createLog();//Создадим лог-файл
	initAll();//Инициализируем всё
	createPlayers();

	LoadCards();//Загрузим все карты

	if (debugMode)
	{
		createProcesses("p1.exe", "p2.exe");
		loadDeck("test.txt", 0);
		loadDeck("test.txt", 1);
		processDrawACard(0);
		processDrawACard(0);
		processDrawACard(0);
		processDrawACard(1);
		processDrawACard(1);
		processDrawACard(1);
		processDrawACard(1);
	}

	cout << "READY" << endl;

	if (debugMode)
	{
		player = 0;
		while (!gameExit)
		{
			processTurnMain();
		}

	}


	system("PAUSE");

	return 0;
}