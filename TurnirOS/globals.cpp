#include "globals.h"

/*
Нужна функция логирования. Пусть пишет в обычный txt файл.
*/

// Decks
vector<Card*> deck[2];

// Hands
vector<Card*> hand[2];

// info heroes
int health[2];

int mana[2];
int maxMana[2];

// info game
int turn; // номер хода
int player; // кто из игроков ходит
// info table
Card * table[2][7]; // pole
bool tableCheck[2][7]; // temp. unit exist true/false

int selected;
int target;

bool refresh = false;
vector<Card*> DataBase;
int debugVal = 0;
ofstream Qlog("log.txt");
bool gameExit = false;

int qqq()
{
	return 0;
}
std::stringstream que1, que2;
HANDLE hChildStdin_R1, hChildStdin_W1;
HANDLE hChildStdout_R1, hChildStdout_W1;

HANDLE hChildStdin_R2, hChildStdin_W2;
HANDLE hChildStdout_R2, hChildStdout_W2;

PROCESS_INFORMATION pi1, pi2;

vector<char> message1, message2;

map<string, int>COMMANDS = { { "-PLAY", 0 },{ "-ATTACK", 1 },{ "-END_TURN", 2 },{ "-GET_TABLE", 3}, {"-GET_INFO",4}, {"-GET_HAND",5}, {"-CONCEDE", 6} };
//Функции для работы с дочерними процессами

void WriteToPipe(HANDLE read, HANDLE write, CHAR chBuf[], int size)
{
	DWORD dwWritten;
	BOOL bSuccess = FALSE;

	bSuccess = WriteFile(write, chBuf, size, &dwWritten, NULL);
}

void ReadFromPipe(HANDLE read, HANDLE write, CHAR chBuf[], DWORD size)
{
	BOOL bSuccess = FALSE;

	bSuccess = ReadFile(read, chBuf, BUFSIZE, &size, NULL);
}

BOOL RunProcess(const char *lpApplicationName, HANDLE pipeRead, HANDLE pipeWrite, DWORD dwWaitMilliseconds, PROCESS_INFORMATION &PI, STARTUPINFOA &SI)
{
	STARTUPINFOA si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));

	si.cb = sizeof(si);

	si.hStdInput = pipeRead;
	si.hStdOutput = pipeWrite;
	si.dwFlags |= STARTF_USESTDHANDLES;

	if (!CreateProcessA(const_cast<LPSTR>(lpApplicationName),
		"",
		NULL,
		NULL,
		TRUE,
		0,
		NULL,
		NULL,
		&si,
		&pi)
		)
	{
		std::cout << "CreateProcess failed [" << GetLastError() << "]\n";
		return FALSE;
	}

	//Все рекомендую закрывать поток с той стороны, но из-за того, что поток я завершаю через TerminateProcess это не обязательно
	//CloseHandle(pipeRead);
	//CloseHandle(pipeWrite);

	PI = pi;
	SI = si;

	return TRUE;
}

//Log-функции
ofstream *logFile;

void createLog()
{
	SYSTEMTIME now;
	GetSystemTime(&now);
	string logName = "Log" + to_string(now.wDay) + to_string(now.wHour) + to_string(now.wMinute) + to_string(now.wSecond) + ".txt";
	logFile->open(logName, std::ios::out);
}

void writeToLog(string st)
{
	(*logFile) << st;
}

void closeLog()
{
	logFile->close();
}
