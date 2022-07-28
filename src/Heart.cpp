// Heart.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Heart.h"
#include <algorithm>
#include <cstring>

using namespace std;
using namespace heart;

std::vector<string> ScriptLines;
std::vector<string> NameSpaces;
std::vector<heart::BOOL> BoolVariables;
std::vector<heart::INT> IntVariables;
std::vector<heart::STRING> StringVariables;

int codeLine = 0;

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "ru");

	while (true) {
		char inputComm[1024];
		printf(">>> ");
		scanf("%s", inputComm);

		const char* command = inputComm;
		std::string preCommand = command;

		if(preCommand == "ex()")
			exit(-1);
		if (preCommand == sysClean)
			clean();

		if (preCommand == sysHelp)
			printf("\nКомманды:\n%s : Чистка экрана\n%s : Помощь с командами\n%s : Открывает файл\nex() : Закрытие интерпретатора\n\n", sysClean.c_str(), sysHelp.c_str(), sysOpen.c_str());

		if (preCommand == sysOpen) {

			printf(">>> Файл для открытия (без расширения): ");
			scanf("%s", inputComm);
			std::string tempScr = inputComm;
			tempScr += scriptFormat;
			command = tempScr.c_str();
			std::string strs = command;
			int LastLength = strs.length();
			std::string fileName;
			for (int n = 0; n < LastLength; n++) {
				fileName += tempScr[n];
			}

			std::ifstream ffrom;
			ffrom.open(fileName);

			if (!ffrom.is_open())
				printf("\n>>> Ошибка чтения\n>>> Не удалось открыть файл\n");
			else {
				std::string str;
				while (!ffrom.eof()) {
					str = "";
					std::getline(ffrom, str);
					ScriptLines.push_back(str);
					SyntaxCheck(str);
					codeLine++;
				}
			}
			ffrom.close();
			BoolVariables.clear();
			NameSpaces.clear();
			IntVariables.clear();
			StringVariables.clear();
			codeLine = 0;
		}
	}

	return 0;
}
void SyntaxCheck(std::string& str)
{
	if (str[0] == comment || str[0] == '\0' || str[0] == '\n')
		return;
	checkForTR(str);
	checkForNVariable(str);
	checkForAssigningVar(str);
	checkForPrint(str);
	checkForInput(str);
	checkForSPrint(str);
	checkForSInput(str);
	checkForClean(str);
	checkForClose(str);
}
#pragma region Syntax
void checkForAssigningVar(std::string& str)
{
	std::string codePart = str;
	std::string validCode = "";
	std::string assignTo = "";
	std::string assignType = "";
	const string setIntT = "=";
	const string intT = "I";
	const string subInt = "-";
	const string subIntVar = "#";
	const string addInt = "+";
	const string addIntVar = "$";
	const string convertBtoI = "C";
	const string stringT = "S";
	const string boolT = "B";
	string sval = "";

	for (int i = setVar.length() + 1; i < codePart.length(); i++)
	{
		if (codePart[i] != ' ' || codePart[i] != assign && codePart[i] != endCL)
			assignTo += codePart[i];
		if (codePart[i] == ' ' || codePart[i] == assign)
			i = codePart.length();
	}

	if (assignTo == " " || assignTo == "")
		return;

	int totLength = setVar.length() + 1 + assignTo.length();
	bool assigning = false;

	for (int i = totLength; i < codePart.length(); i++)
	{
		if (codePart[i] == assign && codePart[i - 1] == 'I') {
			assigning = true;
			assignType = intT;
		}
		if (codePart[i] == assign && codePart[i - 1] == '+') {
			assigning = true;
			assignType = addInt;
		}
		if (codePart[i] == assign && codePart[i - 1] == '-') {
			assigning = true;
			assignType = subInt;
		}
		if (codePart[i] == assign && codePart[i - 1] == '#') {
			assigning = true;
			assignType = subIntVar;
		}
		if (codePart[i] == assign && codePart[i - 1] == '$') {
			assigning = true;
			assignType = addIntVar;
		}
		if (codePart[i] == assign && codePart[i - 1] == 'S') {
			assigning = true;
			assignType = stringT;
		}
		if (codePart[i] == assign && codePart[i - 1] == 'B') {
			assigning = true;
			assignType = boolT;
		}
		if (codePart[i] == assign && codePart[i - 1] == 'C') {
			assigning = true;
			assignType = convertBtoI;
		}
		if (assigning && codePart[i] != endCL && codePart[i] != assign && codePart[i] != ' ' && codePart[i] != '"')
			sval += codePart[i];
	}
	heart::STRING stringe("", "");
	heart::INT intege("", 0);
	heart::BOOL boole("","");
	int toChange = 0;
	if (assignType == intT) {
		for (size_t i = 0; i < IntVariables.size(); ++i)
		{
			if (strcmp(IntVariables[i].name.c_str(), assignTo.c_str()) == 0) {
				intege = IntVariables[i];
				toChange = i;
			}
		}
		IntVariables[toChange].val = atoi(sval.c_str());
		return;
	}
	if (assignType == addInt) {
		for (size_t i = 0; i < IntVariables.size(); ++i)
		{
			if (strcmp(IntVariables[i].name.c_str(), assignTo.c_str()) == 0) {
				intege = IntVariables[i];
				toChange = i;
			}
		}
		IntVariables[toChange].val += atoi(sval.c_str());
		return;
	}
	if (assignType == addIntVar) {
		for (size_t i = 0; i < IntVariables.size(); ++i)
		{
			if (strcmp(IntVariables[i].name.c_str(), assignTo.c_str()) == 0) {
				intege = IntVariables[i];
				toChange = i;
			}
		}
		heart::INT toAdd("", 0);
		for (size_t i = 0; i < IntVariables.size(); ++i)
		{
			if (strcmp(IntVariables[i].name.c_str(), sval.c_str()) == 0) {
				toAdd = IntVariables[i];
			}
		}
		IntVariables[toChange].val += toAdd.val;
		return;
	}
	if (assignType == subInt) {
		for (size_t i = 0; i < IntVariables.size(); ++i)
		{
			if (strcmp(IntVariables[i].name.c_str(), assignTo.c_str()) == 0) {
				intege = IntVariables[i];
				toChange = i;
			}
		}
		IntVariables[toChange].val -= atoi(sval.c_str());
		return;
	}
	if (assignType == subIntVar) {
		for (size_t i = 0; i < IntVariables.size(); ++i)
		{
			if (strcmp(IntVariables[i].name.c_str(), assignTo.c_str()) == 0) {
				intege = IntVariables[i];
				toChange = i;
			}
		}
		heart::INT toAdd("", 0);
		for (size_t i = 0; i < IntVariables.size(); ++i)
		{
			if (strcmp(IntVariables[i].name.c_str(), sval.c_str()) == 0) {
				toAdd = IntVariables[i];
			}
		}
		IntVariables[toChange].val -= toAdd.val;
		return;
	}
	if (assignType == convertBtoI) {
		for (size_t i = 0; i < IntVariables.size(); ++i)
		{
			if (strcmp(IntVariables[i].name.c_str(), assignTo.c_str()) == 0) {
				intege = IntVariables[i];
				toChange = i;
			}
		}
		for (size_t i = 0; i < BoolVariables.size(); ++i)
		{
			if (strcmp(BoolVariables[i].name.c_str(), sval.c_str()) == 0) {
				boole = BoolVariables[i];
				toChange = i;
			}
		}
		int value = 0;
		if(boole.val == boolVarA){
			value = 1;
		}else{
			value = 0;
		}
		IntVariables[toChange].val = value;
		return;
	}
	if (assignType == boolT) {
		for (size_t i = 0; i < BoolVariables.size(); ++i)
		{
			if (strcmp(BoolVariables[i].name.c_str(), assignTo.c_str()) == 0) {
				boole = BoolVariables[i];
				toChange = i;
			}
		}
		BoolVariables[toChange].val = sval;
		return;
	}
	if (assignType == stringT) {
		for (size_t i = 0; i < StringVariables.size(); ++i)
		{
			if (strcmp(StringVariables[i].name.c_str(), assignTo.c_str()) == 0) {
				stringe = StringVariables[i];
				toChange = i;
			}
		}
		StringVariables[toChange].val = sval;
		return;
	}
}
void checkForClose(std::string& str) {
	int toChange = 0;
	string nameS = "";
	for (size_t i = 0; i < NameSpaces.size(); ++i)
	{
		if (strcmp(NameSpaces[i].c_str(), nsSys.c_str()) == 0) {
			nameS = NameSpaces[i];
			toChange = i;
		}
	}

	if (nameS != nsSys)
		return;

	string syntaxValid = "";

	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] != endCL)
			syntaxValid += str[i];
	}

	if (syntaxValid != sysClose)
		return;
	exit(-1);
}
void checkForSPrint(std::string& str)
{
	int c = 0;
	bool isReady = false;
	std::string codePart = str;
	std::string validCode = "";
	std::string printType = "";
	std::string typeInt = "I";
	std::string typeString = "S";
	std::string typeBool = "B";
	std::string msg = "";

	for (int i = 0; i < printsFn.length(); i++)
	{
		validCode += codePart[i];
	}
	if (validCode != printsFn)
		return;
	for (int i = printsFn.length() + 2; i < codePart.length(); i++)
	{
		if (!isReady) {
			if (codePart[i] != endCL)
				msg += codePart[i];
			else {
				isReady = true;
			}
		}
	}

	printType += codePart[printsFn.length()];

	int toChange = 0;
	heart::STRING msgS("", "");
	heart::INT msgI("", 0);
	heart::BOOL msgB("", "");
	for (size_t i = 0; i < StringVariables.size(); ++i)
	{
		if (strcmp(StringVariables[i].name.c_str(), msg.c_str()) == 0) {
			msgS = StringVariables[i];
			toChange = i;
		}
	}
	for (size_t i = 0; i < IntVariables.size(); ++i)
	{
		if (strcmp(IntVariables[i].name.c_str(), msg.c_str()) == 0) {
			msgI = IntVariables[i];
			toChange = i;
		}
	}
	for (size_t i = 0; i < BoolVariables.size(); ++i)
	{
		if (strcmp(BoolVariables[i].name.c_str(), msg.c_str()) == 0) {
			msgB = BoolVariables[i];
			toChange = i;
		}
	}

	codePart = "";
	if (isReady) {
		if (printType == typeString) {
			printf(msgS.val.c_str());
			printf("\n");
			StringVariables[toChange].isUsing = true;
		}
		if (printType == typeInt) {
			printf("%d", msgI.val);
			printf("\n");
			IntVariables[toChange].isUsing = true;
		}
		if (printType == typeBool) {
			printf(msgB.val.c_str());
			printf("\n");
			BoolVariables[toChange].isUsing = true;
		}
		isReady = false;
	}
}
void checkForNVariable(std::string& str)
{
	std::string codePart = str;
	std::string validCode = "";
	string type = "";
	string name = "";
	string val = "";

	for (int i = 0; i < codePart.length(); i++)
	{
		if (type != typeString && codePart[i] != ' ' || type != typeInt && codePart[i] != ' ' || type != typeBool && codePart[i] != ' ') {
			type += codePart[i];
		}
		if (type == typeString || type == typeInt || type == typeBool)
			i = codePart.length();
	}

	for (int i = type.length() + 1; i < codePart.length(); i++)
	{
		if (codePart[i] != ' ' || codePart[i] != assign && codePart[i] != endCL)
			name += codePart[i];
		if (codePart[i] == ' ' || codePart[i] == assign)
			i = codePart.length();
	}

	if (name == " " || name == "")
		return;

	int totLength = type.length() + 1 + name.length();
	bool assigning = false;

	for (int i = totLength; i < codePart.length(); i++)
	{
		if (codePart[i] == assign)
			assigning = true;
		if (assigning && codePart[i] != endCL && codePart[i] != assign && codePart[i] != ' ' && codePart[i] != '"')
			val += codePart[i];
	}

	if (val == "" && type == typeString)
		val = " ";
	if (val == "" && type == typeInt)
		val = "0";
	if (val == "" && type == typeBool)
		val = boolVarB;

	val = replace(val, '_', ' ');
	name = replace(name, ' ', '\0');
	name = replace(name, endCL, '\0');

	if (type == typeString) {
		heart::STRING var(name, val);
		StringVariables.push_back(var);
		return;
	}
	if (type == typeBool) {
		heart::BOOL var(name, val);
		if(val == boolVarA || val == boolVarB)
			var = heart::BOOL(name, val);
		BoolVariables.push_back(var);
		return;
	}
	if (type == typeInt) {
		heart::INT integer(name, atoi(val.c_str()));
		IntVariables.push_back(integer);
		return;
	}
}
void checkForTR(std::string& str) {
	bool isReady = false;
	bool startRemove = false;
	std::string codePart = str;
	std::string validCode = "";
	std::string variable = "";

	for (int i = 0; i < attachFn.length(); i++)
	{
		validCode += codePart[i];
	}
	if (validCode != attachFn)
		return;
	if (codePart[validCode.length()] == '<')
		startRemove = true;
	for (int i = attachFn.length() + 1; i < codePart.length(); i++)
	{
		if (startRemove) {
			if (!isReady) {
				if (codePart[i] != endCL && codePart[i] != '<' && codePart[i] != '>') {
					variable += codePart[i];
				}
				if(codePart[i] == endCL || codePart[i] == '>') {
					startRemove = false;
					isReady = true;
				}
			}
		}
	}
	codePart = "";
	if (isReady) {
		NameSpaces.push_back(variable);
	}
}
void checkForInput(std::string& str)
{
	bool isReady = false;
	std::string codePart = str;
	std::string validCode = "";
	std::string msg = "";

	char InputData[1024];

	for (int i = 0; i < inputFn.length(); i++)
	{
		validCode += codePart[i];
	}
	if (validCode != inputFn)
		return;
	for (int i = inputFn.length(); i < codePart.length(); i++)
	{
		if (!isReady) {
			if (codePart[i] != endCL)
				msg += codePart[i];
			else {
				codePart = "";
				isReady = true;
			}
		}
	}
	codePart = "";
	if (isReady) {
		printf(msg.c_str());
		scanf("%s", InputData);
		isReady = false;
	}
}
void checkForSInput(std::string& str)
{
	bool isReady = false;
	std::string codePart = str;
	std::string validCode = "";
	std::string msg = "";

	char InputData[1024];

	for (int i = 0; i < inputsFn.length(); i++)
	{
		validCode += codePart[i];
	}
	if (validCode != inputsFn)
		return;
	for (int i = inputsFn.length(); i < codePart.length(); i++)
	{
		if (!isReady) {
			if (codePart[i] != endCL)
				msg += codePart[i];
			else {
				codePart = "";
				isReady = true;
			}
		}
	}	
	heart::STRING msdg("", "");
	int toChange = 0;
	for (size_t i = 0; i < StringVariables.size(); ++i)
	{
		if (strcmp(StringVariables[i].name.c_str(), msg.c_str()) == 0) {
			msdg = StringVariables[i];
			toChange = i;
		}
	}
	codePart = "";
	if (isReady) {
		scanf("%s", InputData);
		const char* string = InputData;
		StringVariables[toChange].val = string;
		StringVariables[toChange].isUsing = true;
		isReady = false;
	}
}
void checkForClean(std::string& str)
{
	int toChange = 0;
	string nameS = "";
	for (size_t i = 0; i < NameSpaces.size(); ++i)
	{
		if (strcmp(NameSpaces[i].c_str(), nsSys.c_str()) == 0) {
			nameS = NameSpaces[i];
			toChange = i;
		}
	}

	if (nameS != nsSys)
		return;


	string syntaxValid = "";

	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] != endCL)
			syntaxValid += str[i];
	}

	if (syntaxValid != sysClean)
		return;

	clean();
}
void checkForPrint(std::string& str)
{
	int c = 0;
	bool isReady = false;
	std::string codePart = str;
	std::string validCode = "";
	std::string msg = "";

	for (int i = 0; i < printFn.length(); i++)
	{
		validCode += codePart[i];
	}
	if (validCode != printFn)
		return;
	for (int i = printFn.length(); i < codePart.length(); i++)
	{
		if (!isReady) {
			if (codePart[i] != endCL)
				msg += codePart[i];
			else {
				codePart = "";
				isReady = true;
			}
		}
	}
	codePart = "";
	if (isReady) {
		printFunc(msg);
		isReady = false;
	}
}
void printFunc(std::string& msg)
{
	printf("%s\n", msg.c_str());
}
#pragma endregion