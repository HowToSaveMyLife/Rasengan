//#define VarsTest
#ifdef VarsTest
#include <cstdio>
#include <bits/stdc++.h>
#include "Tokenizer.h"
#include "VarManager.h"
#include "OperatorsDefine.h"
#include "Operator.h"
#include "Analyze.h"
#include "FuncManager.h"


int main() {
	Tokenizer tokenizer;
	VarManager globalVars;
	VarManager localVars;
	OperatorManager operators;
	FuncManager funcs;

	operators.add_operator(operatorsInitList);
	tokenizer.load_map_data(operators.make_keywordsList());
	
	/*
	FILE* InputStr;
	freopen_s(&InputStr, "VarsTest_InputStr.txt", "r", stdin);
	//*/

	ifstream InputStr;
	InputStr.open("VarsTest_InputStr.txt");

	std::string str;
	while (str!="EOF") {
		getline(InputStr, str);
		//calculate(str, operators, tokenizer, funcs, globalVars, localVars);
		std::cout << str << std::endl;
		analyze(str, operators, tokenizer, funcs, globalVars, globalVars);
		globalVars.printAllInfo();
		std::cout << std::endl;
	}
	std::cin.clear();

	
	return 0;
}


#endif