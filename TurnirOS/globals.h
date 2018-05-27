#pragma once
#include "cards.h"
#include "Windows.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include <sstream>

/*
void WriteToPipe(HANDLE read, HANDLE write, CHAR chBuf[], int size);
	������� ������ � �����
	read - ������� ����� ��� ������
	write - ������� ����� ��� ������
	chBuf - �����-������. � ���� ����� �������� ������
	size - ������ ��������� ���������� � ������

void ReadFromPipe(HANDLE read, HANDLE write, CHAR chBuf[], DWORD size);
	read - ������� ����� ��� ������
	write - ������� ����� ��� ������
	chBuf - ����� � ������� ��� ��������. ������ ������ ������������� \0
	size - ������ �������� ���������� � ������� � ������

BOOL RunProcess(const char *lpApplicationName, HANDLE pipeRead, HANDLE pipeWrite, DWORD dwWaitMilliseconds, PROCESS_INFORMATION &PI, STARTUPINFOA &SI);
	lpApplicationName - ������ ���� �� ������������ exe �����
	pipeRead - ������� ����� ��� ������
	pipeWrite - ������� ����� ��� ������
	dwWaitMilliseconds - ����� ����� ��������. INFINITE - ����� �������� �������
	PI - ��������� ���������� ��������. ����� ������� ��� ���������� ������ � ���������
	SI - ��������� ���������� ��� ���������� ������ � ���������

void createLog();
	������� ������� ����� ���-����

void writeToLog(string st);
	������� ������ � ��� ����. ���������� ������ "��� ����"
	st - ������ ��� ������ � ��� ����

void closeLog();
	������� �������� ��� �����
*/

using namespace std; 

extern std::stringstream que1, que2;

extern HANDLE hChildStdin_R1, hChildStdin_W1;
extern HANDLE hChildStdout_R1, hChildStdout_W1;

extern HANDLE hChildStdin_R2, hChildStdin_W2;
extern HANDLE hChildStdout_R2, hChildStdout_W2;

extern PROCESS_INFORMATION pi1, pi2;

const int BUFSIZE = 64;

extern map<string, int>COMMANDS;

class Card;

// Decks
extern vector<Card*> deck[2];

// Hands
extern vector<Card*> hand[2];

// info heroes
extern int health[2];
extern int mana[2];
extern int maxMana[2];

// info game
extern int turn; // ����� ����
extern int player; // ��� �� ������� �����

// info table
extern Card * table[2][7]; // pole
extern bool tableCheck[2][7]; // temp. unit exist true/false

extern int selected;
extern int target;

// OS information
extern bool refresh;
extern vector<Card*> DataBase;

extern ofstream *logFile;



void WriteToPipe(HANDLE read, HANDLE write, CHAR chBuf[], int size);
void ReadFromPipe(HANDLE read, HANDLE write, CHAR chBuf[], DWORD size);

BOOL RunProcess(const char *lpApplicationName, HANDLE pipeRead, HANDLE pipeWrite, DWORD dwWaitMilliseconds, PROCESS_INFORMATION &PI, STARTUPINFOA &SI);

void createLog();
void writeToLog(string st);
void closeLog();

extern int debugVal;
extern ofstream Qlog;
extern bool gameExit;
int qqq();