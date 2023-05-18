#pragma once
#include <string>
#include <map>
#include <iostream>

class Var {
private:
	std::string _type;
	std::string _value;
	std::string _unit;

public:
	Var();
	~Var();
	Var(std::string type, std::string value, std::string unit);

	std::string type();
	std::string value();
	std::string unit();
};

