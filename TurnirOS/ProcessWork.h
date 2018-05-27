#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include "globals.h"



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