#include "Operator.h"

Operator::Operator() {
	this->_code = "";
	this->_PRI = 0;
	this->func_2 = nullptr;
}

Operator::Operator(std::string code, int PRI, ValueType(*func1)(ValueType), ValueType(*func2)(ValueType, ValueType))
{
	this->_code = code;
	this->_PRI = PRI;
	this->func_1 = func1;
	this->func_2 = func2;
}

bool Operator::operator<(const Operator& B)
{
	return this->_code<B._code;
}


OperatorManager::OperatorManager()
{
}

OperatorManager::~OperatorManager()
{
	this->OperatorList.clear();
}

void OperatorManager::add_operator(Operator x)
{
	this->OperatorList[x._code] = x;
}

void OperatorManager::add_operator(std::vector<Operator> operatorsInitList)
{
	for (int i = 0; i < operatorsInitList.size(); i++) {
		this->add_operator(operatorsInitList[i]);
	}
}

Operator OperatorManager::get_operator(std::string code)
{
	if (this->OperatorList.count(code))
		return this->OperatorList[code];
	else
		return NullOperator;
}

std::vector<KeyWordPack> OperatorManager::make_keywordsList()
{
	std::vector<KeyWordPack> keyword_list;
	for (auto iter : this->OperatorList) {
		keyword_list.push_back(KeyWordPack("operator", iter.second._code, 0));
	}
	return keyword_list;
}

void OperatorManager::printAllInfo()
{
	std::cout << "Operators{";
	for (auto iter : this->OperatorList) {
		std::cout << "(" << iter.first << "," << iter.second._PRI << "," << iter.second.func_1 << "," << iter.second.func_2 << "), ";
	}
	std::cout << "}";
}
