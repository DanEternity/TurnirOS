#include<iostream>
#include<cmath>
#include<algorithm>
#include<vector>
#include<globals.h>
#include<cards.h>
#include<work.h>
#include <ctime>
using namespace std;

const bool debugMode = false;
const bool mainMode = true;
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
	srand(time(NULL));

//	createLog();//Создадим лог-файл
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
	string p1exe, p2exe;
	string d1, d2;
	if (mainMode)
	{
		health[0] = 30;
		health[1] = 30;
		ifstream qcin("init.cfg");
		qcin >> d1 >> d2 >> p1exe >> p2exe;
		qcin.close();
		createProcesses(p1exe, p2exe);
		loadDeck(d1, 0);
		loadDeck(d2, 1);
		shuffleDeck(0);
		shuffleDeck(1);
		processDrawACard(0);
		processDrawACard(0);
		processDrawACard(0);
		processDrawACard(1);
		processDrawACard(1);
		processDrawACard(1);
		processDrawACard(1);
		// send data to players
		//
		writeHod(0);
		getHand(0);
		getHand(1);
		// get data from players
		//

		Sleep(1000);

		int type, dst, scr, p1, p2;
		getAction(type, scr, dst, p2, p1);
		
		gameStart = false;

		int t1[3], t2[4];

		t1[0] = p1 / 100;
		t1[1] = (p1 % 100) / 10;
		t1[2] = (p1 % 10);

		t2[0] = p2 / 1000;
		t2[1] = (p2 % 1000) / 100;
		t2[2] = (p2 % 100) / 10;
		t2[3] = (p2 % 10);
		int p1draw = 0;
		int p2draw = 0;
		for (int i(0); i<3; i++)
			if (t1[i] == 0)
			{
				Qlog << "0 REDRAW " << i << endl;
				deck[0].push_back(hand[0][i]);
				hand[0].erase(hand[0].begin() + i);
				p1draw++;
			}

		for (int i(0); i<4; i++)
			if (t2[i] == 0)
			{
				Qlog << "1 REDRAW " << i << endl;
				deck[1].push_back(hand[1][i]);
				hand[1].erase(hand[1].begin() + i);
				p2draw++;
			}

		// shuffle decks

		shuffleDeck(0);
		shuffleDeck(1);

		for (int i(0); i < p1draw; i++) processDrawACard(0);
		for (int i(0); i < p2draw; i++) processDrawACard(1);


	}

	cout << "READY" << endl;

	if (mainMode)
	{
		player = 0;
		turn = 1;
		while (!gameExit)
		{
			Qlog << "TURN " << turn << " PLAYER: " << player << endl;
			processTurnMain();
			turn++;
			 
		}
		Qlog.close();
		mlog.close();
		cout << "GAME OVER ON TURN " << turn << endl;
	}


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