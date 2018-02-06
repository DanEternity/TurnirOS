#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <fstream>

#include "globals.h"
#include "cards.h"
#include "work.h"

using namespace std;

const bool debugMode = true;

void initAll()
{
	//�������������� ��������� ����� ������� ������
	mana[0] = 0;
	maxMana[0] = 0;
	health[0] = 30;
	
	//�������������� ��������� ����� ������� ������
	mana[1] = 0;
	maxMana[1] = 0;
	health[1] = 30;

	//��������� ������� ��� ��� ������
	turn = 0;

	//������� ����
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
	createLog();//�������� ���-����
	initAll();//�������������� ��
	createPlayers();

	LoadCards();//�������� ��� �����

	if (debugMode)
	{
		loadDeck("test.txt", 0);
		loadDeck("test.txt", 1);
	}



	closeLog();

	return 0;
}