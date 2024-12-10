#pragma once
#include <string>
#include <vector>
#include <map>
#include "VarManager.h"
#include "Operator.h"
#include "Tokenizer.h"
//#include "Analyze.h"

class FuncManager;

HP_complex calculate(string str, OperatorManager& operatorManager, Tokenizer& tokenizer, FuncManager& funcs, VarManager& globalVars, VarManager& localVars);

void analyze(string str, OperatorManager& operatorManager, Tokenizer& tokenizer, FuncManager& funcs, VarManager& globalVars, VarManager& funcVars);

// ValueType(*func1)(ValueType)

typedef Var(*BuildinFunc)(std::vector<Var>);

class Func {
private:
	std::string name;
	//std::string type;

	//Var (*buildinFunc)(std::vector<Var> varList);
	BuildinFunc buildFunc;

	std::string description;
	std::vector<std::string> argumentList;
	VarManager formal_argument;
	std::string body;
public:
	Func();
	Func(std::string name, BuildinFunc buildFunc, std::string description, std::vector<std::string> argumentList);
	int argNum();
	std::string get_name();
 	void define_name(std::string name);
	void define_argumentList(std::string str);
	void define_description(std::string str);
	void define_body(std::string str);
	void load_args(std::string str, OperatorManager& operatorManager, Tokenizer& tokenizer, FuncManager& funcs, VarManager& globalVars);
	void printAllInfo();
	void printArgumentList();
	std::string get_description();
	Var run(OperatorManager& operatorManager, Tokenizer& tokenizer, FuncManager& funcs, VarManager& globalVars);
};



class FuncManager {
public:
	std::map<std::string, Func> funcList;
	//std::map<std::string, >

	FuncManager();
	~FuncManager();

	void load_func(Func func);
	bool is_exist(std::string name);
	Func get_func(std::string name);
	void load_buildinFuncs(std::vector<Func> buildFuncsList);

	void printAllInfo();
};