#include "Tokenizer.h"

TokenizerRet::TokenizerRet()
{
	this->_type = "undefined";
	this->_value = "null";
	this->_valueNum = 0;
}

TokenizerRet::~TokenizerRet()
{
}

TokenizerRet::TokenizerRet(std::string type, std::string value, int valueNum)
{
	this->_type = type;
	this->_value = value;
	this->_valueNum = 0;
}

std::string TokenizerRet::type()
{
	return this->_type;
}

std::string TokenizerRet::value()
{
	return this->_value;
}

int TokenizerRet::valueNum()
{
	return this->_valueNum;
}

void TokenizerRet::printAllInfo()
{
	std::cout << "TokenizerRet{";
	std::cout << "type:" << std::setw(20) << this->_type << ", ";
	std::cout << "valueNum:" << std::setw(5) << this->_valueNum << ", ";
	std::cout << "value: " << this->_value << " }";
	
}

Tokenizer::Tokenizer()
{
}

Tokenizer::~Tokenizer()
{
}

void Tokenizer::load_map_data(std::string type, std::string value, int valueNum)
{
	this->value_type_map[value] = type;
	this->value_valueNum_map[value] = valueNum;
}

void Tokenizer::load_map_data(std::vector<KeyWordPack> keyword_list)
{
	for (int i = 0; i < keyword_list.size(); i++) {
		this->value_type_map[keyword_list[i]._value] = keyword_list[i]._type;
		this->value_valueNum_map[keyword_list[i]._value] = keyword_list[i]._valueNum;
	}
}

void Tokenizer::printAllInfo()
{
	std::cout << "Tokenizer{";
	std::cout << "keyword_list{";
	for (auto it : this->value_type_map) {
		std::cout << "(" << it.first << "," << this->value_type_map[it.first] << "," << this->value_valueNum_map[it.first] << ") ";
	}
	std::cout << "}";
}

std::string Tokenizer::find_keywords(const std::string& str, int pl)
{
	std::string keyword;
	if (pl >= str.length()) return "#null#";
	for (auto it : this->value_type_map) {
		if (pl + it.first.length() > str.length()) continue;
		if (it.first == str.substr(pl, it.first.length())) {
			return it.first;
		}
	}
	return "#null#";
}

TokenizerRet Tokenizer::run(std::string& str)
{
	TokenizerRet ret;
	int pl=0, pr=0;
	std::stack<char> SmallBrackets_stack;
	std::stack<char> SquareBrackets_stack;
	std::stack<char> Braces_stack;
	for (pl = 0; pl < str.length(); pl++) {
		//	Êý×Ö
		if ((str[pl] >= '0' && str[pl] <= '9')) {
			for (pr = pl; ((str[pr + 1] >= '0' && str[pr + 1] <= '9' || str[pr + 1] == '.') && pr < str.length() - 1); pr++) {}
			while (str[pr] < '0' || str[pr]>'9') { pr--; }
			ret = TokenizerRet("number", str.substr(pl, pr - pl + 1), 0);
			str.erase(pl, pr - pl + 1);
			return ret;
		}

		//	¹Ø¼ü×Ö
		std::string keyword = this->find_keywords(str, pl);
		if (keyword != "#null#") {
			str.erase(pl, keyword.length());
			return TokenizerRet(this->value_type_map[keyword], keyword, this->value_valueNum_map[keyword]);
		}

		//	±êÊ¶·û
		if ((str[pl] >= 'A' && str[pl] <= 'Z') || (str[pl] >= 'a' && str[pl] <= 'z') || str[pl] == '_') {
			for (pr = pl; (str[pr] >= 'A' && str[pr] <= 'Z') || (str[pr] >= 'a' && str[pr] <= 'z') || (str[pr] >= '0' && str[pr] <= '9') || str[pr] == '_'; pr++) {}
			pr--;
			ret = TokenizerRet("identifier", str.substr(pl, pr - pl + 1), 0);
			str.erase(pl, pr - pl + 1);
			return ret;
		}

		// ¿é
		//Ð¡À¨ºÅ
		if (str[pl] == '(') {
			while (!SmallBrackets_stack.empty()) SmallBrackets_stack.pop();
			SmallBrackets_stack.push(str[pl]);
			for (pr = pl + 1; !SmallBrackets_stack.empty() && pr < str.length(); pr++) {
				if (str[pr] == '(') SmallBrackets_stack.push(str[pr]);
				else if (str[pr] == ')') {
					if (!SmallBrackets_stack.empty()) SmallBrackets_stack.pop();
					else {
						ret = TokenizerRet("#ERROR#", "SmallBrackets are not matched!", 0);
						return ret;
					}
				}
				else continue;
			}
			pr--;
			if (!SmallBrackets_stack.empty()) {
				ret = TokenizerRet("#ERROR#", "SmallBrackets are not matched!", 0);
				return ret;
			}
			else {
				ret = TokenizerRet("block@SmallBrackets", str.substr(pl, pr - pl + 1), 0);
				str.erase(pl, pr - pl + 1);
				return ret;
			}
		}
		//	ÖÐÀ¨ºÅ
		//ÖÐÀ¨ºÅ
		if (str[pl] == '[') {
			while (!SquareBrackets_stack.empty()) SquareBrackets_stack.pop();
			SquareBrackets_stack.push(str[pl]);
			for (pr = pl + 1; !SquareBrackets_stack.empty() && pr <= str.length(); pr++) {
				if (str[pr] == '[') SquareBrackets_stack.push(str[pr]);
				else if (str[pr] == ']') {
					if (!SquareBrackets_stack.empty()) SquareBrackets_stack.pop();
					else {
						ret = TokenizerRet("#ERROR#", "SquareBrackets are not match!", 0);
						return ret;
					}
				}
				else continue;
			}
			pr--;
			if (!SquareBrackets_stack.empty()) {
				ret = TokenizerRet("#ERROR#", "SquareBrackets are not match!", 0);
				return ret;
			}
			else {
				ret = TokenizerRet("block@SquareBrackets", str.substr(pl, pr - pl + 1), 0);
				str.erase(pl, pr - pl + 1);
				return ret;
			}
		}
		//	´óÀ¨ºÅ
		if (str[pl] == '{') {
			while (!Braces_stack.empty()) Braces_stack.pop();
			Braces_stack.push(str[pl]);
			for (pr = pl + 1; !Braces_stack.empty() && pr <= str.length(); pr++) {
				if (str[pr] == '{') Braces_stack.push(str[pr]);
				else if (str[pr] == '}') {
					if (!Braces_stack.empty()) Braces_stack.pop();
					else {
						ret = TokenizerRet("#ERROR#", "Braces are not match!", 0);
						return ret;
					}
				}
				else continue;
			}
			pr--;
			if (!Braces_stack.empty()) {
				ret = TokenizerRet("#ERROR#", "Braces are not match!", 0);
				return ret;
			}
			else {
				ret = TokenizerRet("block@Braces", str.substr(pl, pr - pl + 1), 0);
				str.erase(pl, pr - pl + 1);
				return ret;
			}
		}
	}
	return TokenizerRet("#OVER#", "null", 0);
}

KeyWordPack::KeyWordPack()
{
	this->_type = "undefined";
	this->_value = "null";
	this->_valueNum = 0;
}

KeyWordPack::KeyWordPack(std::string type, std::string value, int valueNum)
{
	this->_type = type;
	this->_value = value;
	this->_valueNum = valueNum;
}
