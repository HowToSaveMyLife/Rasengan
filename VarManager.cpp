#include "VarManager.h"

Var::Var()
{
	this->_name = "";
	this->_type = "";
	this->_value = "";
	this->_unit = "";
}

Var::~Var()
{
}

Var::Var(std::string name, std::string type, std::string value, std::string unit)
{
	this->_name = name;
	this->_type = type;
	this->_value = value;
	this->_unit = unit;
}

void Var::load(std::string name, std::string type, std::string value, std::string unit)
{
	this->_name = name;
	this->_type = type;
	this->_value = value;
	this->_unit = unit;
}

void Var::load(std::string type, std::string value, std::string unit)
{
	this->_type = type;
	this->_value = value;
	this->_unit = unit;
}


std::string Var::name()
{
	return this->_name;
}

std::string Var::type()
{
	return this->_type;
}

std::string Var::value()
{
	return this->_value;
}

std::string Var::unit()
{
	return this->_unit;
}

VarManager::VarManager()
{
}

VarManager::~VarManager()
{
	this->varList.clear();
}

bool VarManager::is_exist(std::string name)
{
	if (this->varList.end() != this->varList.find(name))
		return true;
	else
		return false;
}

void VarManager::update_var(Var var)
{
	this->varList[var.name()] = var;
}

void VarManager::update_var(std::string name)
{
	this->varList[name] = Var(name,"","","");
}

Var VarManager::get_var(std::string name)
{
	if (this->is_exist(name))
		return this->varList[name];
	else
		return Var("null", "#error#", name + " can't find", "");
}

void VarManager::printAllInfo()
{
	std::cout << "VarManager{ \n";
	for (auto iter : this->varList) {
		std::cout << "	( " << iter.first << ", " << iter.second.type() << ", " << iter.second.value() << ", " << iter.second.unit() << "); \n";
	}
	std::cout << " }";
}
