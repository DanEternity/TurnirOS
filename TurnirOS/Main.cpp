#include<iostream>
#include<cmath>
#include<algorithm>
#include<vector>
#include<globals.h>
#include<cards.h>
#include<work.h>

using namespace std;

//KEK

int main()
{
	const bool debugMode = true;

	// 
	// initialization
	//

	mana[0] = 0;
	mana[1] = 0;
	maxMana[0] = 0;
	maxMana[1] = 0;
	health[0] = 30;
	health[1] = 30;
	turn = 0;
	for (int i(0); i < 2; i++)
		for (int j(0); j < 7; j++)
			tableCheck[i][j] = false;


	LoadCards();

	if (debugMode)
	{
		loadDeck("test.txt", 0);
		loadDeck("test.txt", 1);
	}



	return 0;
}