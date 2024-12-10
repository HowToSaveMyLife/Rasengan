//#define AnalyzeTest
#ifdef AnalyzeTest
#include <cstdio>
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


	//std::vector<KeyWordPack> operatorList;

	operators.add_operator(operatorsInitList);

	/*
	operatorList = operators.make_keywordsList();

	for (int i = 0; i < operatorList.size(); i++) {
		std::cout << operatorList[i]._type << " " << operatorList[i]._value << std::endl;
	}
	*/

	tokenizer.load_map_data(operators.make_keywordsList());
	/*
	operators.printAllInfo();
	std::cout << std::endl;
	tokenizer.printAllInfo();
	std::cout << std::endl;
	*/
	HP_complex ANS;
	//*
	FILE* InputStr;
	freopen_s(&InputStr, "AnalyzeTest_InputStr.txt", "r", stdin);
	std::string str;
	while (std::cin >> str) {
		ANS = calculate(str, operators, tokenizer,funcs, globalVars, localVars);
		ANS.out();
		std::cout << std::endl;
	}
	std::cin.clear();
	//*/
	return 0;
}


#endif