//#define FuncsTest
#ifdef FuncsTest
#include <cstdio>
#include <bits/stdc++.h>
#include "Tokenizer.h"
#include "VarManager.h"
#include "OperatorsDefine.h"
#include "Operator.h"
#include "Analyze.h"
#include "BuildinFuncDefine.h"
#include "FuncManager.h"


int main() {
	Tokenizer tokenizer;
	VarManager globalVars;
	VarManager localVars;
	OperatorManager operators;
	FuncManager funcs;

	funcs.load_buildinFuncs(buildinFuncsList);
	operators.add_operator(operatorsInitList);
	//operators.printAllInfo();
	tokenizer.load_map_data(operators.make_keywordsList());

	/*
	FILE* InputStr;
	freopen_s(&InputStr, "VarsTest_InputStr.txt", "r", stdin);
	//*/

	ifstream InputStr;
	InputStr.open("FuncsTest_InputStr.txt");

	std::string str;
	std::string str_all;
	while (str != "EOF") {
		getline(InputStr, str);
		//calculate(str, operators, tokenizer, funcs, globalVars, localVars);
		//std::cout << str << std::endl;
		str_all += str;
		//analyze(str, operators, tokenizer, funcs, globalVars, globalVars);
		//funcs.printAllInfo();
		//std::cout << std::endl;
	}
	analyze(str_all, operators, tokenizer, funcs, globalVars, globalVars);
	std::cin.clear();


	return 0;
}


#endif