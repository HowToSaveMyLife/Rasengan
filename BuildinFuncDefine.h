#pragma once
#include "FuncManager.h"

std::string func_a_add_b_minus_c_name = "fantastic";
std::vector<std::string> func_a_add_b_minus_c_varList = {"a","b","c"};
std::string func_a_add_b_minus_c_description = "(a,b,c) return a+b-c";
Var func_a_add_b_minus_c(std::vector<Var> varList) {
	HP_complex a;
	HP_complex b;
	HP_complex c; 

	a.readStr(varList[0].value());
	b.readStr(varList[1].value());
	c.readStr(varList[2].value());
	

	HP_complex ans;
	ans = a + b;
	ans = ans - c;
	return Var("#RETURN#", "complex", ans.ToString(), "1");
}

std::string bool_not_name = "not";
std::vector<std::string> bool_not_varList = {"x"};
std::string bool_not_description = "(x) return not x";
Var bool_not(std::vector<Var> varList) {
	HP_complex x;

	x.readStr(varList[0].value());

	HP_complex ans;
	HP_fraction zero("0");

	if (x.real() == zero && x.imag() == zero)
		ans = HP_complex("1", "0");
	else
		ans = HP_complex("0", "0");

	return Var("#RETURN#", "complex", ans.ToString(), "1");
}

std::string func_exp_name = "exp";
std::vector<std::string> func_exp_varList = { "x","n"};
std::string func_exp_description = "(x,n) return not exp(x) 精度为小数点后n位";
Var func_exp(std::vector<Var> varList) {
	HP_complex x;
	int n = stoi(varList[1].value());
	x.readStr(varList[0].value());

	HP_fraction tmp;

	tmp = x.real().exp(n);
	
	HP_complex ans(tmp,HP_fraction("0"));

	return Var("#RETURN#", "complex", ans.ToString(), "1");
}

std::string func_ln_name = "ln";
std::vector<std::string> func_ln_varList = { "x" ,"n"};
std::string func_ln_description = "(x) return not ln(x) 精度为小数点后n位";
Var func_ln(std::vector<Var> varList) {
	HP_complex x;
	int n = stoi(varList[1].value());
	x.readStr(varList[0].value());

	HP_fraction tmp;

	tmp = x.real().ln(n);

	HP_complex ans(tmp, HP_fraction("0"));

	return Var("#RETURN#", "complex", ans.ToString(), "1");
}

std::string func_sqrt_name = "sqrt";
std::vector<std::string> func_sqrt_varList = { "x","n"};
std::string func_sqrt_description = "(x,n) return not sqrt(x) 精度为小数点后n位";
Var func_sqrt(std::vector<Var> varList) {
	HP_complex x;
	int n = stoi(varList[1].value());
	x.readStr(varList[0].value());

	HP_fraction tmp;

	tmp = x.real().sqrt(n);

	HP_complex ans(tmp, HP_fraction("0"));

	return Var("#RETURN#", "complex", ans.ToString(), "1");
}

std::vector<Func> buildinFuncsList = {
	Func(func_a_add_b_minus_c_name,func_a_add_b_minus_c,func_a_add_b_minus_c_description,func_a_add_b_minus_c_varList),
	Func(bool_not_name,bool_not,bool_not_description,bool_not_varList),
	Func(func_exp_name,func_exp,func_exp_description,func_exp_varList),
	Func(func_ln_name,func_ln,func_ln_description,func_ln_varList),
	Func(func_sqrt_name,func_sqrt,func_sqrt_description,func_sqrt_varList),
};