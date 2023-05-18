#pragma once
#include <string>
#include <map>
#include <vector>
#include <iostream>

class BaseUnit {
private:
	std::string _name;
	std::string _code;	// µ¥Î»·ûºÅ±àÂë

public:
	BaseUnit();
	~BaseUnit();

	BaseUnit(std::string name, std::string code);

	std::string name();
	std::string code();

	bool operator < (const BaseUnit& B);
	bool operator == (const BaseUnit& B);
	bool operator > (const BaseUnit& B);
	bool operator != (const BaseUnit& B);
	void printAllInfo();
};

struct BaseUnitNode {
	BaseUnitNode* pre;
	double trans_factor_pre;
	BaseUnit value;
	std::vector<BaseUnitNode*> next;
	std::vector<double> trans_factor_next;

	BaseUnitNode();
	~BaseUnitNode();

	void add_nextNode(BaseUnitNode& node);
	void link_preNode(BaseUnitNode& node);
};

class BaseUnitManager {
private:
	std::vector<BaseUnitNode> rootUnits;
	std::map<std::string, BaseUnitNode*> codeList;

public:
	

};