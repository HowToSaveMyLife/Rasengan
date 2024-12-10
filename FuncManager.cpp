#include "FuncManager.h"

Func::Func()
{
	this->name = "";
	this->description = "";
	this->body = "";
	this->buildFunc = nullptr;

}

Func::Func(std::string name, BuildinFunc buildFunc, std::string description, std::vector<std::string> argumentList)
{
	this->name = name;
	this->buildFunc = buildFunc;
	this->description = description;
	this->argumentList = argumentList;
}

int Func::argNum()
{
	return this->argumentList.size();
}

std::string Func::get_name()
{
	return this->name;
}

void Func::define_name(std::string name)
{
	this->name = name;
}


void Func::define_argumentList(std::string str)
{
	TokenizerRet tokenizerRet;
	Tokenizer tokenizer;
	std::string argList_str = str.substr(1,str.size()-2);
	do {
		tokenizerRet = tokenizer.run(argList_str);
		if (tokenizerRet.type() == "identifier") {
			this->argumentList.push_back(tokenizerRet.value());
		}
	} while (tokenizerRet.type() != "#OVER#" && tokenizerRet.type() != "#ERROR#");
}

void Func::define_description(std::string str)
{
	this->description = str;
}

void Func::define_body(std::string str)
{
	std::string body_str = str.substr(1, str.size() - 2);
	this->body = body_str;
}

//*
void Func::load_args(std::string str, OperatorManager& operatorManager, Tokenizer& tokenizer,FuncManager& funcs, VarManager& globalVars)
{
	std::string args_str = str.substr(1, str.size() - 2);
	int counter = 0;
	int pos;
	HP_complex arg_value;
	do {
		pos = args_str.find(',');

		//std::cout << "POS:" << pos << std::endl;

		if (pos == -1) {
			arg_value = calculate(args_str.substr(0, pos), operatorManager, tokenizer, funcs, globalVars, globalVars);
			this->formal_argument.update_var(Var(this->argumentList[counter], std::string("complex"), arg_value.ToString(), std::string("1")));
			//std::cout << args_str << std::endl;
			/*
			arg_value.out();
			std::cout << std::endl;
			//*/

		}
		else {
			arg_value = calculate(args_str, operatorManager, tokenizer, funcs, globalVars, globalVars);
			this->formal_argument.update_var(Var(this->argumentList[counter], std::string("complex"), arg_value.ToString(), std::string("1")));
			args_str.erase(0, pos + 1);
			/*
			arg_value.out();
			std::cout << std::endl;
			//*/

		}
		counter++;
	} while (pos != -1);
	//this->printArgumentList();
	/*
	cout << "%%%%%%%%" << endl;
	this->formal_argument.printAllInfo();
	cout << "%%%%%%%%%%%%%%%%%" << endl;
	*/
}
void Func::printAllInfo()
{
	std::cout << "Func{" << this->name << ", (";
	for (int i = 0; i < this->argumentList.size(); i++) {
		if (i != 0)
			std::cout << "," << this->argumentList[i];
		else
			std::cout << this->argumentList[i];
	}
	std::cout << "), " << this->body << " }";
}
void Func::printArgumentList()
{
	cout << "### ";
	for (int i = 0; i < this->argumentList.size(); i++) {
		std::cout << this->argumentList[i] << ", ";
	}
	cout << " ###";
}
std::string Func::get_description()
{
	return this->description;
}
//*/

Var Func::run(OperatorManager& operatorManager, Tokenizer& tokenizer, FuncManager& funcs, VarManager& globalVars)
{
	if (this->buildFunc == nullptr) {
		Var ANS;
		analyze(this->body, operatorManager, tokenizer, funcs, globalVars, this->formal_argument);
		ANS = this->formal_argument.get_var("#RETURN#");
		return ANS;
	}
	else {
		std::vector<Var> varList;
		std::string varName;
		for (int i = 0; i < this->argumentList.size(); i++) {
			varName = this->argumentList[i];
			varList.push_back( this->formal_argument.get_var(varName) );
		}
		Var ANS;
		ANS = this->buildFunc(varList);
		return ANS;
	}
	
}

FuncManager::FuncManager()
{
}

FuncManager::~FuncManager()
{
}

void FuncManager::load_func(Func func)
{
	this->funcList[func.get_name()] = func;
}

bool FuncManager::is_exist(std::string name)
{
	if (this->funcList.end() != this->funcList.find(name))
		return true;
	else
		return false;
}

Func FuncManager::get_func(std::string name)
{
	return this->funcList[name];
}

void FuncManager::load_buildinFuncs(std::vector<Func> buildFuncsList)
{
	for (int i = 0; i < buildFuncsList.size(); i++) {
		this->funcList[buildFuncsList[i].get_name()] = buildFuncsList[i];
	}
}

void FuncManager::printAllInfo()
{
	std::cout << "FuncsManager{" << std::endl;
	for (auto iter : this->funcList) {
		std::cout << "	";
		iter.second.printAllInfo();
		std::cout << std::endl;
	}
	std::cout << "}" << std::endl;
}
