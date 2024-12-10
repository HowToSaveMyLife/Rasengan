#pragma once
#include <string>
#include <map>
#include <vector>
#include "Tokenizer.h"
#include "HP_complex.h"
#define ValueType HP_complex

class Operator {
public:
	std::string _code;	//	��������ʶ��
	int _PRI;			//	���������ȼ�(����˳��Ϊ�����ȼ��Ľ�������)
	ValueType (*func_1)(ValueType A);				//	��Ŀ�������������
	ValueType (*func_2)(ValueType A, ValueType B);	//	˫Ŀ�������������

	Operator();

	Operator(std::string code, int PRI, ValueType(*func1)(ValueType), ValueType(*func2)(ValueType, ValueType));

	bool operator < (const Operator& B);
};

const Operator NullOperator("NullOperator", -1, nullptr, nullptr);

class OperatorManager {
private:
	std::map<std::string, Operator> OperatorList;


public:

	OperatorManager();
	~OperatorManager();

	void add_operator(Operator x);
	void add_operator(std::vector<Operator> operatorsInitList);
	Operator get_operator(std::string code);

	std::vector<KeyWordPack> make_keywordsList();

	void printAllInfo();
};


