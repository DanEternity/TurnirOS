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

map<string, int>COMMANDS = { { "play", 0 },{ "attack", 1 },{ "endturn", 2 } };
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

BOOL createProcesses(std::string st1, std::string st2)
{
	std::string pname1 = st1;
	std::string pname2 = st2;
	STARTUPINFOA si1, si2;

	SECURITY_ATTRIBUTES sa;
	ZeroMemory(&sa, sizeof(SECURITY_ATTRIBUTES));
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.bInheritHandle = true;
	sa.lpSecurityDescriptor = NULL;
	if (!CreatePipe(&hChildStdin_R1, &hChildStdin_W1, &sa, 0))
		std::cout << "CreatePipe Error" << std::endl;

	if (!CreatePipe(&hChildStdout_R1, &hChildStdout_W1, &sa, 0))
		std::cout << "CreatePipe Error" << std::endl;

	if (!CreatePipe(&hChildStdin_R2, &hChildStdin_W2, &sa, 0))
		std::cout << "CreatePipe Error" << std::endl;

	if (!CreatePipe(&hChildStdout_R2, &hChildStdout_W2, &sa, 0))
		std::cout << "CreatePipe Error" << std::endl;


	RunProcess(pname1.c_str(), hChildStdin_R1, hChildStdout_W1, INFINITE, pi1, si1);
	RunProcess(pname2.c_str(), hChildStdin_R2, hChildStdout_W2, INFINITE, pi2, si2);

	return true;
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
