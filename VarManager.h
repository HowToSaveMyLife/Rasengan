#pragma once
#include <string>
#include <map>
#include <iostream>

class Var {
private:
	std::string _name;
	std::string _type;
	std::string _value;
	std::string _unit;

public:
	Var();
	~Var();
	Var(std::string name, std::string type, std::string value, std::string unit);

	void load(std::string name, std::string type, std::string value, std::string unit);
	void load(std::string type, std::string value, std::string unit);

	std::string name();
	std::string type();
	std::string value();
	std::string unit();
};

class VarManager {
private:
	std::map<std::string, Var> varList;
public:
	VarManager();
	~VarManager();
	bool is_exist(std::string name);
	void update_var(Var var);
	void update_var(std::string name);
	Var get_var(std::string name);

	void printAllInfo();
};