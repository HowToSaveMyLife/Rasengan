#define TokenizerTest
#ifdef TokenizerTest
#include <cstdio>
#include "Tokenizer.h"

int main() {
	Tokenizer tokenizer;
	FILE* InputStr;
	FILE* InputKey;
	freopen_s(&InputKey, "Tokenizer_test_InputKey.txt", "r", stdin);
	//freopen_s(&InputStr, "Tokenizer_test_InputStr.txt", "r", stdin);
	std::vector<KeyWordPack> keyWordList;
	std::string tmpValue;
	std::string tmpType;
	int tmpInt;

	while (std::cin >> tmpValue) {
		std::cin >> tmpType;
		std::cin >> tmpInt;
		keyWordList.push_back(KeyWordPack(tmpType, tmpValue, tmpInt));
		//std::cout << "[ " << tmpValue << "| " << tmpType << "| " << tmpInt << "]" << std::endl;
	}
	std::cin.clear();
	freopen_s(&InputStr, "Tokenizer_test_InputStr.txt", "r", stdin);
	std::string str;
	getline(std::cin, str);
	TokenizerRet unit;


	tokenizer.load_map_data(keyWordList);
	tokenizer.printAllInfo();
	std::cout << std::endl;

	std::cout << "Input: " << str << '\n';
	while (unit.type() != "#OVER#" && unit.type() != "#ERROR#") {
		unit = tokenizer.run(str);
		unit.printAllInfo();
		std::cout << '\n';
	}

	return 0;
}

#endif