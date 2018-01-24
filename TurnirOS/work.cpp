#include "work.h"

void processAttack(int scr, int trg)
{
	selected = scr;
	target = trg;

	// tmp version

	table[1-player][target]->Def -= table[player][selected]->Atk;
	table[player][selected]->Def -= table[1-player][target]->Atk;

	/* LOG? */

	/* ADD EFFECT IF CURSE */

	// tmp check death
	if (table[player][selected]->isCurse)
		table[1 - player][target]->Def = -999;

	if (table[1 - player][target]->isCurse)
		table[player][selected]->Def = -999;

	if (table[1 - player][target]->Def <= 0)
		destroyCard(1 - player, target);

	if (table[player][selected]->Def <= 0)
		destroyCard(player, selected);

}

void processPlayCard(int card, int pos, int trg)
{
	selected = pos;
	target = target; // can take more than 0..6 numbers; 10..16 mean enemy size; 
	
	if (hand[player][card]->isSpell)
	{
		// PLAY AS SPELL
	}
	else
	{
		// PLAY AS CREATURE
		table[player][selected] = new Card(hand[player][card]);
		// ACTIVATE ABILITIES
		
		// Init
		table[player][selected]->isCanAttack = true;
		// ������� ���� ���� ������ �� ����� ����� ��������� ���� isStorm.
		// ���� � ����� isCanAttack = false �� isStorm ������������� �� �����
	}
}

void destroyCard(int side, int pos)
{
	// add to log?


	//

	if (table[side][pos]->isLastWord) // check to LAST WORD
	{
		/* IN LOG THIS SHOULD BE LIKE  */
		/* CARD DESTROYED; LAST WORD ACTIVATED; */
		/* BUT IN REAL SITUATION WE CANT REMOVE CARD BEFORE LAST WORD ACTIVATED */
		Card * LW = table[side][pos]; // SAVE POINTER TO LAST WORD CARD */
		table[side][pos]->effPTR(); // LAST WORD EFFECT SHOULD NOT DESTROY CARD
		LW->~Card();
	}
	else
		table[side][pos]->~Card();
	
}

void processTurnMain()
{
	// START OF THE TURN

	// LOG();

	// INIT
	
	maxMana[player] = min(10, maxMana[player] + 1);
	mana[player] = maxMana[player];

	// DRAW A CARD
	
	processDrawACard(player);

	// ACTIVATING START TURN ABILITIES
	// if they exist...

	// Actually start of the turn

	while (1)
	{

		// Here 2(3) types of actions
		// 1: PLAY A CARD
		// 2: Attack an enemy (hero, creature)
		// 3: concede (ROFL) (hope this function will never be called)

		// ���� �� ���� ��� ������ �������� �������
		// ������� ������ �������, ������� ���-�� ��� ������ ����������
		// �� ���� ������� ������������� �� ����

		int type; 
		int scr;
		int dst;
		int param;
		int code;

		getAction(type, scr, dst, param, code); // get an Action

		switch (type)
		{
		case 1: // PLAY A CARD
			
			// � ������ ��� ���� �� ��������� � processPlayCard();

			// scr = card in your hand
			// dst = position on table where card should be plased
			// param...
			// maybe it can be impossible to know exist param or no...
			// so...
			// getAction should simply check that a specific card require a @param@ field
			// it can be made with isTargetable and isSpell
			// in all other situasions all other field should be zero (except scr)

			// SO HERE WE ALREADY KNOW THAT SPECIFIC CARD EXIST IN HAND

			// CHECK IF MANA AVAILABLE
			
			if (hand[player][scr]->manaCost)
			{
				// We want to play hand[player][scr] card
				if (hand[player][scr] -> isSpell)
				{
					// I THINK HERE SHOULD BE CORRECTNESS CHECK...
					
					// FOR EXAMPLE YOU CANT HEAL ENEMY!!!

					if (1 /*CORRECT*/)
						processPlayCard(scr, dst, param); // PlayCard
					else
					{
						// LOG ERROR
						// INCORRECT PLAY
					}
				}
				else
					if (getTableCardCount(player) == 7)
					{
						// LOG ERROR
						// NO FREE SPACE
					}
					else
					{
						if (hand[player][scr]->isTargetable)
						{
							// Check target correctness

							if (1 /*Correct*/)
							{
								if (tableCheck[player][dst])
								{
									// ZONE IS NOT AVAILABLE

									// we should move all other creatures...

									// but i dont want to write this...

								}

								processPlayCard(scr, dst, param); // PlayCard
							}
							else
							{
								// LOG ERROR
							}

						}
					}
			}
			else
			{
				// LOG ERROR
				// NOT ENOUGTH MANA
			}
			break;
		case 2: // ATTACK
		{
			// ����� �� �������...

			// �������� �� ���� �� �����������...

			int tt = getLeftTaunt(player); // res < 0 ���� ������� ������ ���

			if (tt < 0)
				processAttack(scr, dst);
			else
			{
				if (tableCheck[1-player][dst] && table[1 - player][dst]->isTaunt)
					processAttack(scr, dst); // ���� �� � ��� ������� ����������, �� �����
				else
					processAttack(scr, tt); // ��������� ����������
			}
			
			break;
		}
		/* ������� ����� getHand � getTable ����� �������� ����� ��, � �� ������ � ���� ���� */
		default: // I DONT THINK THAT THIS IS REALLY POSSIBLE =)
			break;
		}

		// ��������� ���� ���-�� � ���� �� <= 0 
		// �� ������ ������
		// Curse ������������ ������� �����, ������� ������� � -999 ���� �� ������
		// � ������-�� ��� ����� �� ��������� ��� ����� ������������� -999.
		// ����� � ���� ��������
		// �� ���-�� ����
		
		for (int i(0); i < 6; i++)
		{
			// �� ������� ���� �� ����� �������, ��� �� ����� ��� ���� � -1 � ����� ��)
			// �� ����� ������ ������� ��������� �������� ������ �����������.
			// ���� �������� � ���������� ������ ������������� ����� ��������� �����-������ �����, �� ��� �� ����� ����������.
			// �������, �� ���� ���� ��� ������� �� ������ ����������
			if (tableCheck[player][i] && table[player][i]->Def <= 0)
				destroyCard(player, i);

			if (tableCheck[1-player][i] && table[1-player][i]->Def <= 0)
				destroyCard(1-player, i);
			// �������� ��������� �� ������� �����-������ ���������� ������� ������� � ���� �� ������.
			// � �� ���� � �������������� ����� ������
		}

	}

	// End of the turn

	// Activating end turn abilities
	// if they exist...

	// SWAP PLAYERS

	player = 1 - player;

}
