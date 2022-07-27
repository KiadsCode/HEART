#pragma once
#include "stdafx.h"
#include "INT.h"
#include "STRING.h"
#include "BOOL.h"
#include <stdlib.h>
#include "SharedConst.h"

void clean() {
	system("cls");
}
std::string replace(std::string& source, char oldChar, char newChar) {
	std::string edited = source;
	for (int i = 0; i < edited.length(); i++)
	{
		if (edited[i] == oldChar)
			edited[i] = newChar;
	}
	return edited;
}
void checkForIfOperation(std::string& str);

void checkForAssigningVar(std::string& str);

void checkForSPrint(std::string& str);

void checkForPrint(std::string& str);

void checkForClose(std::string& str);

void checkForTR(std::string& str);

void checkForClean(std::string& str);

void SyntaxCheck(std::string& str);

void checkForNVariable(std::string& str);

void checkForInput(std::string& str);

void checkForSInput(std::string& str);

void printFunc(std::string& msg);
