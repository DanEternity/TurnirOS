#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include "globals.h"

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