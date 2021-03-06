#include "globals.h"

/*
����� ������� �����������. ����� ����� � ������� txt ����.
*/

// Decks
vector<Card*> deck[2];

// Hands
vector<Card*> hand[2];

// info heroes
int health[2];

int mana[2];
int maxMana[2];

int fatique[2] = { 0, 0 };

// info game
int turn; // ����� ����
int player; // ��� �� ������� �����
// info table
Card * table[2][7]; // pole
bool tableCheck[2][7]; // temp. unit exist true/false

int selected;
int target;

bool refresh = false;
vector<Card*> DataBase;
int debugVal = 0;
ofstream Qlog("log.txt");
ofstream mlog("players_log.txt");
bool gameExit = false;
bool gameStart = true;

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

map<string, int>COMMANDS = { { "-PLAY", 1 },{ "-ATTACK", 2 },{ "-END_TURN", 3 },{ "-GET_TABLE", 4}, {"-GET_INFO",5}, {"-GET_HAND",6}, {"-CONCEDE", 7} };
//������� ��� ������ � ��������� ����������

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

	//��� ���������� ��������� ����� � ��� �������, �� ��-�� ����, ��� ����� � �������� ����� TerminateProcess ��� �� �����������
	//CloseHandle(pipeRead);
	//CloseHandle(pipeWrite);

	PI = pi;
	SI = si;

	return TRUE;
}

void createProcesses(string st1, string st2)
{
	STARTUPINFOA si1, si2;

	SECURITY_ATTRIBUTES sa;
	ZeroMemory(&sa, sizeof(SECURITY_ATTRIBUTES));
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.bInheritHandle = true;
	sa.lpSecurityDescriptor = NULL;
	if (!CreatePipe(&hChildStdin_R1, &hChildStdin_W1, &sa, 0))
		cout << "CreatePipe Error" << endl;

	if (!CreatePipe(&hChildStdout_R1, &hChildStdout_W1, &sa, 0))
		cout << "CreatePipe Error" << endl;

	if (!CreatePipe(&hChildStdin_R2, &hChildStdin_W2, &sa, 0))
		cout << "CreatePipe Error" << endl;

	if (!CreatePipe(&hChildStdout_R2, &hChildStdout_W2, &sa, 0))
		cout << "CreatePipe Error" << endl;


	RunProcess(st1.c_str(), hChildStdin_R1, hChildStdout_W1, INFINITE, pi1, si1);
	RunProcess(st2.c_str(), hChildStdin_R2, hChildStdout_W2, INFINITE, pi2, si2);
}

//Log-�������
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
