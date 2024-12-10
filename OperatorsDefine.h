#pragma once
#include "Operator.h"
#define ValueType HP_complex

HP_complex _Operator_J("0", "1");
//HP_complex _Operator_ONE("1", "0");
//HP_complex _Operator_ZERO("0", "0");

// 运算符关联函数
ValueType nullOperator(ValueType A, ValueType B) {
	return HP_complex();
}
ValueType add(ValueType A, ValueType B) {
	return A + B;
}
ValueType sub(ValueType A, ValueType B) {
	return A - B;
}
ValueType mul(ValueType A, ValueType B) {
	return A * B;
}
ValueType div(ValueType A, ValueType B) {
	//HP_complex t = B;
	return A / B;
}
ValueType factorial(ValueType A) {
	HP_fraction t;
	t = A.real().factorial();
	HP_complex B(t,HP_fraction("0"));
	return B;
}

ValueType _pow(ValueType A, ValueType B) {
	//	return pow(A, B);
	HP_complex ANS;
	ANS = A ^ B;
	return ANS;
}

ValueType minusSign(ValueType A) {
	return HP_complex() - A;
}

ValueType j2imag(ValueType A) {
	//HP_complex	J("0", "1");
	return A * _Operator_J;
}

ValueType is_larger(ValueType A, ValueType B) {
	HP_fraction B_f;
	B_f = B.real();
	if (A.real() > B_f)
		return HP_complex("1", "0");
	else
		return HP_complex("0", "0");
}

ValueType is_notlarger(ValueType A, ValueType B) {
	HP_fraction B_f;
	B_f = B.real();
	if (A.real() > B_f)
		return HP_complex("0", "0");
	else
		return HP_complex("1", "0");
}

ValueType is_smaller(ValueType A, ValueType B) {
	HP_fraction B_f;
	B_f = B.real();
	if (A.real() < B_f)
		return HP_complex("1", "0");
	else
		return HP_complex("0", "0");
}

ValueType is_notsmaller(ValueType A, ValueType B) {
	HP_fraction B_f;
	B_f = B.real();
	if (A.real() < B_f)
		return HP_complex("0", "0");
	else
		return HP_complex("1", "0");
}

ValueType is_equal(ValueType A, ValueType B) {
	HP_fraction B_f;
	B_f = B.real();
	if (A.real() == B_f)
		return HP_complex("1", "0");
	else
		return HP_complex("0", "0");
}

ValueType is_notequal(ValueType A, ValueType B) {
	HP_fraction B_f;
	B_f = B.real();
	if (A.real() == B_f)
		return HP_complex("0", "0");
	else
		return HP_complex("1", "0");
}

ValueType bool_and(ValueType A, ValueType B) {
	HP_fraction zero;
	zero.in("0");
	if (A.real() == zero || B.real() == zero )
		return HP_complex("0", "0");
	else
		return HP_complex("1", "0");
}

ValueType bool_or(ValueType A, ValueType B) {
	HP_fraction zero;
	zero.in("0");
	if (A.real() == zero && B.real() == zero)
		return HP_complex("0", "0");
	else
		return HP_complex("1", "0");
}

// 运算符列表
std::vector<Operator> operatorsInitList = {
	Operator("null",0,nullptr,nullptr),
	Operator("**",3,nullptr,_pow),			//	乘方(借鉴python命名方式)
	Operator("!",3,factorial,nullptr),
	Operator("+",1,nullptr,add),			//	加
	Operator("-",1,minusSign,sub),			//	减(双目)和负号(特殊单目)	
	Operator("*",2,nullptr,mul),			//	乘
	Operator("/",2,nullptr,div),			//	除
	Operator("j",3,j2imag,nullptr),
	//*
	Operator(">",0,nullptr,is_larger),
	Operator("==",0,nullptr,is_equal),
	Operator("<",0,nullptr,is_smaller),
	Operator("!=",0,nullptr,is_notequal),
	Operator("<",0,nullptr,is_smaller),
	Operator(">=",0,nullptr,is_notsmaller),
	Operator("<=",0,nullptr,is_notlarger),
	Operator("||",0,nullptr,bool_or),
	Operator("&&",0,nullptr,bool_and),
	//*/
}; 