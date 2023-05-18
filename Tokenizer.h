#pragma once
#include <string>
#include <vector>
#include <map>
#include <stack>
#include <iostream>
#include <iomanip>

class TokenizerRet {
private:
	std::string _type;
	std::string _value;
	int _valueNum;

public:
	TokenizerRet();
	~TokenizerRet();

	TokenizerRet(std::string type, std::string value, int valueNum);

	std::string type();
	std::string value();
	int valueNum();

	void printAllInfo();

};

struct KeyWordPack {
	std::string _type;
	std::string _value;
	int _valueNum;

	KeyWordPack();
	KeyWordPack(std::string type, std::string value, int valueNum);
};

struct CmpByKeyLength {
	bool operator() (const std::string& key_1, const std::string& key_2) const {
		if (key_1.length() > key_2.length())
			return true;
		else
			return key_1 > key_2;
	}
};

class Tokenizer {
private:
	std::map<std::string, std::string, CmpByKeyLength> value_type_map;
	std::map<std::string, int, CmpByKeyLength> value_valueNum_map;

public:
	Tokenizer();
	~Tokenizer();
	
	void load_map_data(std::string type,std::string value, int valueNum);
	void load_map_data(std::vector<KeyWordPack> keyword_list);
	void printAllInfo();

	std::string find_keywords(const std::string& str, int pl);
	TokenizerRet run(std::string& str);
};