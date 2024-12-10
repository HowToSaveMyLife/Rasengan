#pragma once
# include <iostream>
# include <string>
using namespace std;

//高精整形的一位
struct HP_digit {
	HP_digit* high_digit;
	HP_digit* low_digit;
	unsigned short int digit;
	HP_digit() { high_digit = NULL; low_digit = NULL; digit = 0; };
};

//一个高精整形，有长度、符号、最高位、最低位地址
class HP_int {
private:
	int lenth;
	HP_digit* highest_digit;
	HP_digit* lowest_digit;
	HP_digit* hot_digit;	//便于实现各种操作的指针
public:
	bool sign;
	HP_int();							//构造函数
	HP_int(const HP_int& A);			//复制构造函数
	HP_int(string A);
	~HP_int();							//析构函数
	void free();						//释放所有的HP_digit
	void out();							//在命令行输出高精整形
	string ToString();					//转为字符串
	void del_zeros();					//删除高位的零
	void copy_address(HP_int& A);		//仅复制地址
	int get_lenth();
	void delete_lowdigit(int num);		//辅助分数中的近似用
	void operator=(string s);			//用字符串为高精整形赋值，输入时大于0的数s="123"，小于0的数s="-123"，0均可，但只保存为+0
	void operator=(const HP_int& A);	//拷贝
	bool operator>(HP_int& A);			//高精整形的比较、逻辑运算，均带符号
	bool operator<(HP_int& A);
	bool operator==(HP_int& A);
	bool operator!=(HP_int& A);
	HP_int add(HP_int& A);				//add与minus只实现数值上的加减，不考虑符号，辅助完成高精整形的+-
	HP_int minus(HP_int& minus);
	HP_int decimal(HP_int& A, int num = 10);	//仅求小数部分，num为需要保留小数的位数
	HP_int operator+(HP_int& A);		//高精整形+
	HP_int operator-(HP_int& A);		//高精整形-
	HP_int operator*(HP_int& A);		//高精整形*
	HP_int operator/(HP_int& A);		//高精整形/
	HP_int operator%(HP_int& A);		//高精整形%
	HP_int operator^(HP_int& A);
	HP_int factorial();
};