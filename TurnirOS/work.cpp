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
				s << st[i];//встретили обычный символ
				letter_flag = true;
		}
		else if (letter_flag)//встретили пробел
		{
			s << '\n';//но до этого были символы. Объединяем в токен
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

	if (player == 0)//Первый игрок
	{
		PeekNamedPipe(hChildStdout_R1, chBuf, BUFSIZE, &size, &avail, NULL);//Если в канале что-то есть
		if (avail != 0)
		{
			ZeroMemory(&chBuf, sizeof(chBuf));//Считаем содержимое канала
			ReadFromPipe(hChildStdout_R1, hChildStdout_W1, chBuf, avail);
			std::cout << "Get from 1: " << chBuf << std::endl;
			make_tokens(que1, chBuf, avail);
		}
	}
	else//Второй игрок
	{
		PeekNamedPipe(hChildStdout_R2, chBuf, BUFSIZE, &size, &avail, NULL);
		if (avail != 0)
		{
			ZeroMemory(&chBuf, sizeof(chBuf));
			ReadFromPipe(hChildStdout_R2, hChildStdout_W2, chBuf, avail);
			std::cout << "Get from 2: " << chBuf << std::endl;
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

	int args[3];
	string name, arg;

	int col = getArgumentCount();
	if (player == 0)
	{
		que1 >> name;
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
	if (col >= 1)
		scr = args[0];
	if (col >= 2)
		dst = args[1];
	if (col >= 3)
		param = args[2];
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
	Qlog << 1-player << " ATTACK " << trg << ' ' << scr << "   " << table[1-player][selected]->Atk << " dmg" << endl;
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
	
	//

	if (deck[pl].size() == 0)
	{
		// Draw fatique (1.. 2.. 3.. 4.. и тд урона)

	}
	else
	{
		if (hand[pl].size() == 9)
		{
			// log
			// discard card
			delete hand[pl][0];
		}
		else
			hand[pl].push_back(deck[pl][0]);
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
		// Вначале хода всем картам на столе нужно устновить флаг isStorm.
		// Если у карты isCanAttack = false то isStorm устанавливать не нужно
		tableCheck[player][selected] = true;
	}
}

void destroyCard(int side, int pos)
{
	// add to log?
	Qlog << side << " DESTROYED " << pos << endl;

	//
	tableCheck[side][pos] = false; // Уничтоженная карта не может стать целью заклинания или эффекта.
	// Грубо говоря другие эффекты сработавшие параллельно не будут на неё воздействовать
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
	
	maxMana[player] = min(10, maxMana[player] + 1);//Начисление максимального количества маны
	mana[player] = maxMana[player];//Начисление доступного количества маны
	
	processDrawACard(player);//Взятие карты игроком

	// ACTIVATING START TURN ABILITIES
	// if they exist...

	for (int i(0); i < 7; i++)
		if (tableCheck[player][i])
			table[player][i]->isStorm = true;

	// Actually start of the turn

	while (1)
	{
		// Here 2(3) types of actions
		// 1: PLAY A CARD
		// 2: Attack an enemy (hero, creature)
		// 3: concede (ROFL) (hope this function will never be called)

		// Пока не знаю как должен получать команды
		// поэтому сделаю функцию, которая как-то это должна передовать
		// но саму функцию реализовывать не буду

		int type; 
		int scr;
		int dst;
		int param;
		int code;

		getAction(type, scr, dst, param, code); //Функция получения команды от игрока

		switch (type)
		{
		case 1: // PLAY A CARD
			
			// А вообще это надо всё перенести в processPlayCard();

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

							if (0 /*Correct*/) // нужно написать общую функцию, которая по айди карты и параметрам разыгровки (по герою, по существу
								// по своему существу, по вражескому и тд.) будет определять корректен ли такой ход для такой карты)
							{
								break;
							}	
						}
						if (tableCheck[player][dst])
						{
							// ZONE IS NOT AVAILABLE

							// we should move all other creatures...

							// будем пытаться сначала переместить вправо

							// найдём пустое место...
							int emp = -1;
							for (int i(dst+1); i < 7; i++) // А ВООБЩЕ НАДО БЫЛО СДЕЛАТЬ КАК В SV И ПОСЛАТЬ ИГРОКА НАХУЙ
								// И ВСЕГДА РАЗЫГРЫВАТЬ В САМУЮ ПРАВУЮ СВОБОДНУЮ ЯЧЕЙКУ АВТОМАТИЧЕСКИ
								// И да у меня реально есть желание запретить разыгрывать карты в занятые ячейки
							{
								if (!tableCheck[player][i])
								{
									emp = i;
									break;
								}
							}
							if (emp == -1)
							{
								// Справа места нет. Двигаем влево...
								for (int i(dst - 1); i >= 0; i--)
									if (!tableCheck[player][i])
									{
										emp = i;
										break;
									}
							}
							// Очевидно... что теперь место есть... (если его нет, то это бред, потому что существ меньше 7, а ячеек как раз 7)
							tableCheck[player][emp] = true;
							if (emp > dst)
							{
								// сдвигаем вправо
								// ЭТО СКОРЕЕ ВСЕГО НУЖНО ЛОГИРОВАТЬ
								// ПОТОМУ ЧТО ВИЗУАЛЬНО ТО ИЗМЕНЕНИЕ ПРОИЗХОДИТ НА СТОЛЕ
								for (int i(emp); i > dst + 1; i--)
									table[player][i] = table[player][i - 1];
							}
							else
							{
								// сдвигаем влево
								// ЭТО СКОРЕЕ ВСЕГО НУЖНО ЛОГИРОВАТЬ
								// ПОТОМУ ЧТО ВИЗУАЛЬНО ТО ИЗМЕНЕНИЕ ПРОИЗХОДИТ НА СТОЛЕ
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
			if (tableCheck[player][scr] && table[player][scr]->isStorm)
			{
				if (dst != -1 && tableCheck[1 - player][dst])
				{
					// Здесь всё сложнее...
					table[player][scr]->isStorm = false;
					// Проверка на удар по провокациям...

					int tt = getLeftTaunt(player); // res < 0 если таунтов вообще нет

					if (tt < 0)
						processAttack(scr, dst);
					else
					{
						if (tableCheck[1 - player][dst] && table[1 - player][dst]->isTaunt)
							processAttack(scr, dst); // ЕСЛИ МЫ И ТАК АТАКУЕМ ПРОВОКАЦИЮ, ТО ПОФИГ
						else
							processAttack(scr, tt); // АТАКОВАТЬ ПРОВОКАЦИЮ
					}
				}
				else
				{
					if (dst == -1)
					{
						table[player][scr]->isStorm = false;
						int tt = getLeftTaunt(player); // res < 0 если таунтов вообще нет
						if (tt < 0)
						{
							Qlog << player << " ATTACK " << scr << ' ' << -1 << "   " << table[player][scr]->Atk << " dmg" << endl;
							health[1 - player] -= table[player][scr]->Atk;
						}
						else
						{
							if (tableCheck[1 - player][dst] && table[1 - player][dst]->isTaunt)
								processAttack(scr, dst); // ЕСЛИ МЫ И ТАК АТАКУЕМ ПРОВОКАЦИЮ, ТО ПОФИГ
							else
								processAttack(scr, tt); // АТАКОВАТЬ ПРОВОКАЦИЮ
						}
					}
				}
			}
			break;
		}
		/* Запросы вроде getHand и getTable можно отвечать сразу же, а не пихать в этот цикл */
		default: 
			break;
		}
		if (type == 3)
		{
			break;
		}
		// Проверяем если кто-то у кого хп <= 0 
		// На всякий случай
		// Curse теоритически убивает сразу, поэтому проблем с -999 быть не должно
		// И вообще-то там урона не наносится там чисто присваивается -999.
		// Можно и флаг возвести
		// но как-то лень
		
		for (int i(0); i < 6; i++) // Этот цикл обязателен я знаю пример, когда без него останется существо с -1 хп и не умрёт
		{
			// По крайней мере мы будем уверены, что на столе нет карт с -1 и менее хп)
			// Но здесь вообще кроется некоторая проблема данной архитектуры.
			// Если например в результате вызова предсмертного хрипа произойдёт какая-нибудь хрень, то это не будет обработано.
			// Впрочем, по идее этот код никогда не должен выполнится
			if (tableCheck[player][i] && table[player][i]->Def <= 0)
				destroyCard(player, i);

			if (tableCheck[1-player][i] && table[1-player][i]->Def <= 0)
				destroyCard(1-player, i);
			// Возможно следовало бы сделать какую-нибудь глобальную очередь событий и туда всё пихать.
			// Я не силён в проектировании таких систем
		}

		// Это не костыль, это упрощённая модель системы событий

		while (refresh)
		{
			refresh = false;
			for (int i(0); i < 6; i++) 
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
			gameExit = true;
			break;
		}

		if (health[1] <= 0)
		{
			Qlog << "PLAYER 2 DEFEATED" << endl;
			gameExit = true;
			break;
		}

	}

	// End of the turn

	// Activating end turn abilities
	// if they exist...

	// SWAP PLAYERS

	player = 1 - player;

}

void loadDeck(string filename, int pl)
{
	ifstream ins(filename);
	
	for (int i(0); i < 30; i++)//Считаем 30 карт из файла игрока
	{
		int idx;//Индекс карты в базе
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
			addToMessage(1-pl, to_string(i) + ' ' + to_string(table[1-pl][i]->id) + ' ' + to_string(table[1-pl][i]->scrManaCost)
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
