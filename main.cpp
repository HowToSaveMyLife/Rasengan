#define _MAIN_
#ifdef _MAIN_
#include <cstdio>
#include <bits/stdc++.h>
#include "Tokenizer.h"
#include "VarManager.h"
#include "OperatorsDefine.h"
#include "Operator.h"
#include "Analyze.h"
#include "BuildinFuncDefine.h"
#include "FuncManager.h"

Tokenizer tokenizer;
VarManager globalVars;
VarManager localVars;
OperatorManager operators;
FuncManager funcs;

std::string inputStr = "";
std::string inputStr_copy = "";

std::string initFileName = "init.txt";

int main() {

	funcs.load_buildinFuncs(buildinFuncsList);
	operators.add_operator(operatorsInitList);
	tokenizer.load_map_data(operators.make_keywordsList());

	inputStr = "import \"" + initFileName + "\"";
	analyze(inputStr, operators, tokenizer, funcs, globalVars, globalVars);

	cout << "Rasengan varsion 0.1.0 alpha" << endl;
	cout << "input \"exit\" to exit; \"help\" for help; \"devlog\" to get develop log" << endl;
	while (true) {
		cout << ">>> ";
		getline(cin, inputStr);
		inputStr_copy = inputStr;
		if (inputStr == "exit") {
			break;
		}
		else if (inputStr == "cls") {
			system("cls");
			continue;
		}
		else if (inputStr == "varslog") {
			globalVars.printAllInfo();
			cout << endl;
			continue;
		}
		else if (inputStr == "funcslog") {
			funcs.printAllInfo();
			cout << endl;
			continue;
		}
		analyze(inputStr, operators, tokenizer, funcs, globalVars, globalVars);
	}
	return 0;
}



#endif