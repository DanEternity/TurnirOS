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
	Функция записи в трубу
	read - Сторона трубы для чтения
	write - Сторона трубы для записи
	chBuf - Буфер-массив. В него будут переданы данные
	size - Размер считанной информации в байтах

void ReadFromPipe(HANDLE read, HANDLE write, CHAR chBuf[], DWORD size);
	read - Сторона трубы для чтения
	write - Сторона трубы для записи
	chBuf - Буфер с данными для передачи. Строка должна заканчиваться \0
	size - Размер полезной информации в массиве в байтах

BOOL RunProcess(const char *lpApplicationName, HANDLE pipeRead, HANDLE pipeWrite, DWORD dwWaitMilliseconds, PROCESS_INFORMATION &PI, STARTUPINFOA &SI);
	lpApplicationName - полный путь до запускаемого exe файла
	pipeRead - сторона трубы для чтения
	pipeWrite - сторона трубы для записи
	dwWaitMilliseconds - время жизни процесса. INFINITE - будет отличным выбором
	PI - Служебная информация процесса. Нужно вернуть для дальнейшей работы с процессом
	SI - Служебная информация для дальнейшей работы с процессом

void createLog();
	Функция создает новый лог-файл

void writeToLog(string st);
	Функция записи в лог файл. Записывает строку "как есть"
	st - строка для записи в лог файл

void closeLog();
	Функция закрытия лог файла
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
extern int turn; // номер хода
extern int player; // кто из игроков ходит

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