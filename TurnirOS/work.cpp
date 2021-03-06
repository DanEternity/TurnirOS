#include "work.h"
#include <Windows.h>
#include "globals.h"

int getTableCardCount(int pl)
{
	int c = 0;
	for (int i(0); i < 7; i++)
		if (tableCheck[pl][i])
			c++;
	return c;
}

void make_tokens(std::stringstream &s, CHAR st[BUFSIZE], int size)
{
	bool letter_flag = false;
	for (int i(0); i < size; i++)
		if (st[i] != ' ')
		{
				s << st[i];//��������� ������� ������
				letter_flag = true;
		}
		else if (letter_flag)//��������� ������
		{
			s << '\n';//�� �� ����� ���� �������. ���������� � �����
			letter_flag = false;
		}
	
	return;
}

void addToMessage(int player, string st)
{
	if(player == 0)
		for (int i(0); i < st.size(); i++)
			message1.push_back(st[i]);
	else for (int i(0); i < st.size(); i++)
			message2.push_back(st[i]);
}

void writePlayerPipe(vector<char>mass, int player);

void sendMessage(int player)
{
	if (player == 0)
		writePlayerPipe(message1, player);
	else writePlayerPipe(message2, player);
}

void writePlayerPipe(vector<char>mass, int player)
{
	CHAR chBuf[BUFSIZE];
	DWORD size(0);
	DWORD avail;

	size = mass.size();
	for (int i(0); i < size; i++)
		chBuf[i] = mass[i];
	
	if (player == 0)
	{
		WriteToPipe(hChildStdin_R1, hChildStdin_W1, chBuf, size);
		message1.clear();
	}
	else
	{
		WriteToPipe(hChildStdin_R2, hChildStdin_W2, chBuf, size);
		message2.clear();
	}
}

void readPlayerPipe()
{
	CHAR chBuf[BUFSIZE];
	DWORD size(0);
	DWORD avail;

	DWORD exit = 0;

	//������ �����
	{
		PeekNamedPipe(hChildStdout_R1, chBuf, BUFSIZE, &size, &avail, NULL);//���� � ������ ���-�� ����
		if (avail != 0)
		{
			ZeroMemory(&chBuf, sizeof(chBuf));//������� ���������� ������
			ReadFromPipe(hChildStdout_R1, hChildStdout_W1, chBuf, avail);
			std::cout << "Get from 1: " << endl << chBuf << std::endl;
			mlog << "Get from 1: " << endl << chBuf << std::endl;
			make_tokens(que1, chBuf, avail);
		}
	}
	//������ �����
	{
		PeekNamedPipe(hChildStdout_R2, chBuf, BUFSIZE, &size, &avail, NULL);
		if (avail != 0)
		{
			ZeroMemory(&chBuf, sizeof(chBuf));
			ReadFromPipe(hChildStdout_R2, hChildStdout_W2, chBuf, avail);
			std::cout << "Get from 2: " << endl << chBuf << std::endl;
			mlog << "Get from 2: " << endl << chBuf << std::endl;
			make_tokens(que2, chBuf, avail);
		}
	}
}

int getArgumentCount()
{
	return 2;//Hi-hi
}

void getAction(int & type, int & scr, int & dst, int & param, int & code)
{
	readPlayerPipe();
	if (gameStart)
	{
		int col = 4;
		int args[4];
		//que1 >> name;
		for (int i(0); i < col; i++)
		{
			string arg;
			que2 >> arg;
			try
			{
				args[i] = std::stoi(arg, nullptr, 10);
			}
			catch (...)
			{
				throw (const char *)"KEK";
			}
		}
		param = args[0] * 1000 + args[1] * 100 + args[2] * 10 + args[3];
		col = 3;
		for (int i(0); i < col; i++)
		{
			string arg;
			que1 >> arg;
			try
			{
				args[i] = std::stoi(arg, nullptr, 10);
			}
			catch (...)
			{
				throw (const char *)"KEK";
			}
		}
		code = args[0] * 100 + args[1] * 10 + args[2];
		return;
	}
	int args[3];
	string name, arg;

	if (player == 0)
	{
		que1 >> name;
		if (COMMANDS.find(name) == COMMANDS.end())
		{
			cout << "ERROR -> " << 0 << " write: " << name << endl;
			return;
		}
		type = COMMANDS.find(name)->second;

		if (name == "-GET_HAND")
		{
			getHand(player);
			
			return;
		}
		if (name == "-GET_TABLE")
		{
			getTable(player);
			
			return;
		}
		if (name == "-GET_INFO")
		{
			getInfo(player);
			
			return;
		}
		if (name == "-END_TURN")
		{
			return;
		}
		int col = getArgumentCount();
		for (int i(0); i < col; i++)
		{
			que1 >> arg;
			try
			{
				args[i] = std::stoi(arg, nullptr, 10);
			}
			catch (...)
			{
				throw (const char *)"KEK";
			}
		}
	}
	else
	{
		que2 >> name;
		if (COMMANDS.find(name) == COMMANDS.end())
		{
			cout << "ERROR -> " << 0 << " write " << name << endl;
			return;
		}
		type = COMMANDS.find(name)->second;

		if (name == "-GET_HAND")
		{
			getHand(player);
			//type = 4;
			return;
		}
		if (name == "-GET_TABLE")
		{
			getTable(player);
			//type = 5;
			return;
		}
		if (name == "-GET_INFO")
		{
			getInfo(player);
			//type = 6;
			return;
		}
		if (name == "-END_TURN")
		{
			return;
		}
		int col = getArgumentCount();
		for (int i(0); i < col; i++)
		{
			que2 >> arg;
			try
			{
				args[i] = std::stoi(arg, nullptr, 10);
			}
			catch (...)
			{
				throw (const char *)"KEK";
			}
		}
	}
	//if (col >= 1)
	scr = args[0];
	//if (col >= 2)
	dst = args[1];
	//if (col >= 3)
	param = args[2] % 30;
}

void processAttack(int scr, int trg)
{
	selected = scr;
	target = trg;

	// tmp version

	table[1-player][target]->Def -= table[player][selected]->Atk;
	table[player][selected]->Def -= table[1-player][target]->Atk;

	/* LOG? */
	Qlog << player << " ATTACK " << scr << ' ' << trg << "   " << table[player][selected]->Atk << " dmg" << endl;
	Qlog << 1-player << " ATTACK " << trg << ' ' << scr << "   " << table[1-player][target]->Atk << " dmg" << endl;
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

void processDrawACard(int pl)
{
	// Log?
	Qlog << pl << " DRAWCARD ";// << //endl;

	//

	if (deck[pl].size() == 0)
	{
		// Draw fatique (1.. 2.. 3.. 4.. � �� �����)
		
		fatique[pl]++;
		health[pl] -= fatique[pl];
		Qlog << "-1 FATIQUE " << fatique[pl] << endl;
	}
	else
	{
		if (hand[pl].size() == 9)
		{
			// log
			// discard card
			Qlog << "DISCARD " << deck[pl][0]->id << ' ' << deck[pl][0]->manaCost << ' ' << deck[pl][0]->Atk << ' ' << deck[pl][0]->Def << endl;
			delete deck[pl][0];
			
		}
		else
		{
			Qlog << deck[pl][0]->id << ' ' << deck[pl][0]->manaCost << ' ' << deck[pl][0]->Atk << ' ' << deck[pl][0]->Def << endl;
			hand[pl].push_back(deck[pl][0]);
		}
		deck[pl].erase(deck[pl].begin() + 0);
		
	}
}

int getLeftTaunt(int pl)
{
	for (int i(0); i < 7; i++)
		if (tableCheck[1 - pl][i] && table[1 - pl][i]->isTaunt)
			return i;
	return -1;
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
		tableCheck[player][selected] = true;
		// ���� � ����� ���� ������, ���������� ��� + Log
		if (table[player][selected]->isFanfare)
		{
			table[player][selected]->effPTR(table[player][selected]);
		}
	}
}

void destroyCard(int side, int pos)
{
	// add to log?
	Qlog << side << " DESTROYED " << pos << endl;

	//
	tableCheck[side][pos] = false; // ������������ ����� �� ����� ����� ����� ���������� ��� �������.
	// ����� ������ ������ ������� ����������� ����������� �� ����� �� �� ��������������
	if (table[side][pos]->isLastWord) // check to LAST WORD
	{
		/* IN LOG THIS SHOULD BE LIKE  */
		/* CARD DESTROYED; LAST WORD ACTIVATED; */
		/* BUT IN REAL SITUATION WE CANT REMOVE CARD BEFORE LAST WORD ACTIVATED */
		Card * LW = table[side][pos]; // SAVE POINTER TO LAST WORD CARD */
		table[side][pos]->effPTR(table[side][pos]); // LAST WORD EFFECT SHOULD NOT DESTROY CARD
		LW->~Card();
	}
	else
	{
	//	table[side][pos]->~Card();
		Card * tmp = table[side][pos];
		//tmp->~Card();
		delete tmp;
	}
	table[side][pos] = NULL;
	
}

void processTurnMain()
{
	// START OF THE TURN

	// LOG();

	// INIT
	
	maxMana[player] = min(10, maxMana[player] + 1);//���������� ������������� ���������� ����
	mana[player] = maxMana[player];//���������� ���������� ���������� ����
	
	processDrawACard(player);//������ ����� �������

	// ACTIVATING START TURN ABILITIES
	// if they exist...

	for (int i(0); i < 7; i++)
		if (tableCheck[player][i])
		{
			if (!table[player][i]->isDisabled)
			{
				table[player][i]->isStorm = true;
				table[player][i]->isRush = false;
			}
			else
			{
				table[player][i]->isStorm = false;
				table[player][i]->isRush = false;
			}
		}
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

		getAction(type, scr, dst, param, code); //������� ��������� ������� �� ������

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
			
			if (hand[player][scr]->manaCost <= mana[player])
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

							if (0 /*Correct*/) // ����� �������� ����� �������, ������� �� ���� ����� � ���������� ���������� (�� �����, �� ��������
								// �� ������ ��������, �� ���������� � ��.) ����� ���������� ��������� �� ����� ��� ��� ����� �����)
							{
								break;
							}	
						}
						if (tableCheck[player][dst])
						{
							// ZONE IS NOT AVAILABLE

							// we should move all other creatures...

							// ����� �������� ������� ����������� ������

							// ����� ������ �����...
							int emp = -1;
							for (int i(dst+1); i < 7; i++) // � ������ ���� ���� ������� ��� � SV � ������� ������ �����
								// � ������ ����������� � ����� ������ ��������� ������ �������������
								// � �� � ���� ������� ���� ������� ��������� ����������� ����� � ������� ������
							{
								if (!tableCheck[player][i])
								{
									emp = i;
									break;
								}
							}
							if (emp == -1)
							{
								// ������ ����� ���. ������� �����...
								for (int i(dst - 1); i >= 0; i--)
									if (!tableCheck[player][i])
									{
										emp = i;
										break;
									}
							}
							// ��������... ��� ������ ����� ����... (���� ��� ���, �� ��� ����, ������ ��� ������� ������ 7, � ����� ��� ��� 7)
							tableCheck[player][emp] = true;
							if (emp > dst)
							{
								// �������� ������
								// ��� ������ ����� ����� ����������
								// ������ ��� ��������� �� ��������� ���������� �� �����
								Qlog << player << " SHIFT " << scr << " RIGHT " << endl;
								for (int i(emp); i >= dst + 1; i--)
									table[player][i] = table[player][i - 1];
							}
							else
							{
								// �������� �����
								// ��� ������ ����� ����� ����������
								// ������ ��� ��������� �� ��������� ���������� �� �����
								Qlog << player << " SHIFT " << scr << " LEFT " << endl;
								for (int i(emp); i < dst - 1; i++)
									table[player][i] = table[player][i + 1];

							}
						}
						Qlog << player << " PLAYCARD " << scr << ' ' << dst << ' ' << param << endl;
						mana[player] -= hand[player][scr]->manaCost;
						processPlayCard(scr, dst, param); // PlayCard
						delete (hand[player][scr]);
						hand[player].erase(hand[player].begin() + scr);
						
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
			if (tableCheck[player][scr] && (table[player][scr]->isStorm || table[player][scr]->isRush))
			{
				if (dst != -1 && tableCheck[1 - player][dst])
				{
					// ����� �� �������...
					table[player][scr]->isStorm = false;
					table[player][scr]->isRush = false;
					// �������� �� ���� �� �����������...

					int tt = getLeftTaunt(player); // res < 0 ���� ������� ������ ���

					if (tt < 0)
						processAttack(scr, dst);
					else
					{
						if (tableCheck[1 - player][dst] && table[1 - player][dst]->isTaunt)
							processAttack(scr, dst); // ���� �� � ��� ������� ����������, �� �����
						else
							processAttack(scr, tt); // ��������� ����������
					}
				}
				else
				{
					if (dst == -1 && (table[player][scr]->isRush == false || table[player][scr]->isStorm == true))
					{
						table[player][scr]->isStorm = false;
						table[player][scr]->isRush = false;
						int tt = getLeftTaunt(player); // res < 0 ���� ������� ������ ���
						if (tt < 0)
						{
							Qlog << player << " ATTACK " << scr << ' ' << -1 << "   " << table[player][scr]->Atk << " dmg" << endl;
							health[1 - player] -= table[player][scr]->Atk;
						}
						else
						{
							if (tableCheck[1 - player][dst] && table[1 - player][dst]->isTaunt)
								processAttack(scr, dst); // ���� �� � ��� ������� ����������, �� �����
							else
								processAttack(scr, tt); // ��������� ����������
						}
					}
				}
			}
			break;
		}
		/* ������� ����� getHand � getTable ����� �������� ����� ��, � �� ������ � ���� ���� */
		default: 
			break;
		}
		if (type == 3)
		{
			break;
		}
		// ��������� ���� ���-�� � ���� �� <= 0 
		// �� ������ ������
		// Curse ������������ ������� �����, ������� ������� � -999 ���� �� ������
		// � ������-�� ��� ����� �� ��������� ��� ����� ������������� -999.
		// ����� � ���� ��������
		// �� ���-�� ����
		
		for (int i(0); i < 7; i++) // ���� ���� ���������� � ���� ������, ����� ��� ���� ��������� �������� � -1 �� � �� ����
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

		// ��� �� �������, ��� ���������� ������ ������� �������

		while (refresh)
		{
			refresh = false;
			for (int i(0); i < 7; i++) 
			{
				if (tableCheck[player][i] && table[player][i]->Def <= 0)
					destroyCard(player, i);

				if (tableCheck[1 - player][i] && table[1 - player][i]->Def <= 0)
					destroyCard(1 - player, i);
			}
		}

		if (health[0] <= 0)
		{
			Qlog << "PLAYER 1 DEFEATED" << endl;
			Qlog << "PLAYER 2 WIN" << endl;
			gameExit = true;
			break;
		}

		if (health[1] <= 0)
		{
			Qlog << "PLAYER 2 DEFEATED" << endl;
			Qlog << "PLAYER 1 WIN" << endl;
			gameExit = true;
			break;
		}

		Sleep(200);

	}

	// End of the turn

	for (int i(0); i < 7; i++)
	{
		if (tableCheck[player][i])
			table[player][i]->isDisabled = false;
	}

	// Activating end turn abilities
	// if they exist...

	// SWAP PLAYERS

	player = 1 - player;

}

void loadDeck(string filename, int pl)
{
	ifstream ins(filename);
	
	for (int i(0); i < 30; i++)//������� 30 ���� �� ����� ������
	{
		int idx;//������ ����� � ����
		ins >> idx;
		deck[pl].push_back(new Card(DataBase[idx]));
		deck[pl][i]->updStats();
	}

	ins.close();
}

void getTable(int pl)
{
	addToMessage(pl, to_string(health[pl]) + ' ' + to_string(health[1 - pl]) + '\n');
	int n = 0, m = 0;
	for (int i(0); i < 7; i++)
	{
		if (tableCheck[pl][i])
			n++;
		if (tableCheck[1 - pl][i])
			m++;
	}
	addToMessage(pl, to_string(n) + ' ' + to_string(m) + '\n');
	for (int i(0); i<7; i++)
		if (tableCheck[pl][i])
		{
			addToMessage(pl, to_string(i) + ' ' + to_string(table[pl][i]->id) + ' ' + to_string(table[pl][i]->scrManaCost)
				+ ' ' + to_string(table[pl][i]->Atk) + ' ' + to_string(table[pl][i]->Def) + ' ' + ((!table[pl][i]->isCanAttack) ? '-' : ((table[pl][i]->isRush || table[pl][i]->isStorm) ? '+' : '-'))
				+ ' ' + table[pl][i]->spec + '\n');
		}
	for (int i(0); i<7; i++)
		if (tableCheck[1-pl][i])
		{
			addToMessage(pl, to_string(i) + ' ' + to_string(table[1-pl][i]->id) + ' ' + to_string(table[1-pl][i]->scrManaCost)
				+ ' ' + to_string(table[1-pl][i]->Atk) + ' ' + to_string(table[1-pl][i]->Def) + ' ' + ((!table[1-pl][i]->isCanAttack) ? '-' : ((table[1-pl][i]->isRush || table[1-pl][i]->isStorm) ? '+' : '-'))
				+ ' ' + table[1-pl][i]->spec + '\n');
		}

	sendMessage(pl);
}

void getHand(int pl)
{
	int n = hand[pl].size();
	addToMessage(pl, to_string(n) + '\n');
	for (int i(0); i < n; i++)
	{
		addToMessage(pl, to_string(hand[pl][i]->id) + ' ' + to_string(hand[pl][i]->manaCost) + ' ' + to_string(hand[pl][i]->Atk)
			+ ' ' + to_string(hand[pl][i]->Def) + ' ' + hand[pl][i]->spec + '\n');
	}
	sendMessage(pl);
}

void getInfo(int pl)
{ 
	addToMessage(pl, to_string(turn) + ' ' + to_string(mana[pl]) + ' ' + to_string(maxMana[pl]) + ' ' + to_string(mana[1 - pl])
		+ ' ' + to_string(maxMana[1 - pl]) + ' ' + to_string(hand[1 - pl].size()) + ' ' + to_string(deck[pl].size()) + ' '
		+ to_string(deck[1 - pl].size()) + '\n');
	sendMessage(pl);
}

void shuffleDeck(int pl)
{
	for (int i(0); i < deck[pl].size(); i++)
	{
		int idx = rand() % deck[pl].size();
		swap(deck[pl][i], deck[pl][idx]);
	}
	Qlog << pl << " SHUFFLE ";
	for (int i(0); i < deck[pl].size(); i++)
	{
		Qlog << deck[pl][i]->id << ' ';
	}
	Qlog << endl;
}

void writeHod(int pl)
{
	addToMessage(0, to_string(1) + '\n');
	sendMessage(0);
	addToMessage(1, to_string(2) + '\n');
	sendMessage(1);
}
