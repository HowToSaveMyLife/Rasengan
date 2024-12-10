#pragma once
# include<iostream>
# include<string>
# include"HP_int.h"
using namespace std;

class HP_fraction {
private:
	HP_int numerator;
	HP_int denominator;
public:
	HP_fraction();								//分子初始化为0，分母为1
	HP_fraction(const HP_fraction& A);
	HP_fraction(string num);
	HP_fraction(string nume, string deno);
	~HP_fraction();								//析构函数
	void out();									//以分数形式输出
	void decimal_out(int num = 5);				//以小数形式输出
	string ToString();							//返回这个分数的字符串形式
	void in(string nume, string denom);			//用两个string给高精分数的分子、分母赋值，方式同高精整形
	void in(string Num);						//小数赋值
	void free();								//释放
	void reduction();							//对分数进行约分
	HP_int gcd();								//求最大公约数
	void copy_address(HP_fraction& A);			//复制地址
	void similar(int num);
	void operator=(string num);
	void operator=(const HP_fraction& A);		// = 复制一份
	bool operator>(HP_fraction& A);				//有符号逻辑运算
	bool operator<(HP_fraction& A);
	bool operator==(HP_fraction& A);
	bool operator!=(HP_fraction& A);


	HP_fraction operator+(HP_fraction& A);		//分数四则运算
	HP_fraction operator-(HP_fraction& A);
	HP_fraction operator*(HP_fraction& A);
	HP_fraction operator/(HP_fraction& A);
	HP_fraction operator^(HP_fraction& A);
	HP_fraction exp(int num = 5);
	HP_fraction exp_base(int num);
	HP_fraction ln(int num = 5);
	HP_fraction ln_base(int num);
	HP_fraction sqrt(int num = 5);
	HP_fraction sqrt_base(int num);
	HP_fraction factorial();
};

HP_fraction log(HP_fraction& A, HP_fraction& M);