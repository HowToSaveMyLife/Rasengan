#pragma once
# include<string>
# include<iostream>
# include"HP_fraction.h"
using namespace std;

class HP_complex {
private:
	HP_fraction Real;
	HP_fraction Imag;
public:
	HP_complex();
	HP_complex(const HP_complex& A);
	HP_complex(string real, string imag);
	HP_complex(HP_fraction A, HP_fraction B);
	HP_complex(string real_up, string real_down, string imag_up, string imag_down);
	~HP_complex();
	void readStr(string var);																//变量输入
	void in(string real_nume, string real_deno, string imag_nume, string imag_deno);		//以string形式输入实部分数的分子、分母，虚部分数的分子分母
	void out();																				//以分数形式输出
	string ToString();																		//转为字符串
	void decimal_out(int num);																//以小数形式输出
	void free();																			//手动释放
	void copy_address(HP_complex& A);														//复制地址
	HP_fraction real();																		//获取复数的实部，返回高精分数
	HP_fraction imag();																		//获取复数的虚部，返回高精分数
	void operator=(const HP_complex& A);
	HP_complex operator+(HP_complex& A);
	HP_complex operator-(HP_complex& A);
	HP_complex operator*(HP_complex& A);
	HP_complex operator/(HP_complex& A);
	HP_complex operator^(HP_complex& A);
};