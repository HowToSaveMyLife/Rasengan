#pragma once
# include "HP_int.h"

HP_int::HP_int() {
	lenth = 0;
	sign = true;
	highest_digit = NULL;
	lowest_digit = NULL;
	hot_digit = NULL;
}

HP_int::HP_int(const HP_int& A) {
	HP_digit* A_hot;

	lenth = A.lenth;
	sign = A.sign;

	lowest_digit = new HP_digit;
	highest_digit = lowest_digit;
	hot_digit = lowest_digit;
	lowest_digit->digit = A.lowest_digit->digit;

	A_hot = A.lowest_digit;
	for (int i = 1; i < lenth; i++) {
		A_hot = A_hot->high_digit;

		highest_digit->high_digit = new HP_digit;
		highest_digit->high_digit->low_digit = highest_digit;
		highest_digit = highest_digit->high_digit;
		highest_digit->digit = A_hot->digit;
	}
}

HP_int::HP_int(string A) {
	*this = A;
}

HP_int::~HP_int() {
	free();
}

void HP_int::free() {
	sign = false;
	while (lenth > 0 && lowest_digit != NULL) {
		highest_digit = highest_digit->low_digit;
		if (highest_digit != NULL) delete highest_digit->high_digit;
		else delete lowest_digit, lowest_digit = NULL, hot_digit = NULL;
		lenth -= 1;
	}
};

void HP_int::out() {
	if (!sign)	cout << '-';
	hot_digit = highest_digit;
	for (int i = 0; i < lenth; i++) {
		cout << hot_digit->digit;
		hot_digit = hot_digit->low_digit;
	}
	hot_digit = lowest_digit;
}

string HP_int::ToString() {
	string ans;
	hot_digit = highest_digit;
	if (!sign) ans = '-';
	while (hot_digit != NULL) {
		char b = hot_digit->digit + 48;
		ans = ans + b;
		hot_digit = hot_digit->low_digit;
	}
	hot_digit = lowest_digit;
	return ans;
}

void HP_int::del_zeros() {
	if (highest_digit->digit == 0 && highest_digit->low_digit != NULL) {
		hot_digit = highest_digit->low_digit;
		delete highest_digit;
		highest_digit = hot_digit;
		highest_digit->high_digit = NULL;
		lenth--;
		del_zeros();
	}
	if (highest_digit->digit == lowest_digit->digit && highest_digit->digit == 0) {
		sign = true;
	}
}

void HP_int::copy_address(HP_int& A) {
	free();
	lenth = A.lenth;
	sign = A.sign;
	hot_digit = A.hot_digit;
	highest_digit = A.highest_digit;
	lowest_digit = A.lowest_digit;
}

int HP_int::get_lenth() {
	return lenth;
}

void HP_int::delete_lowdigit(int num) {
	for (; num > 0; num--) {
		if (lenth > 1) {
			hot_digit = lowest_digit->high_digit;
			delete lowest_digit;
			lowest_digit = hot_digit;
			lowest_digit->low_digit = NULL;
			lenth--;
		}
		else {
			lowest_digit->digit = 0;
		}
	}
}

void HP_int::operator=(string s) {
	if (lowest_digit != NULL) free();

	if (s[0] == '-') {
		sign = false;
		lenth = s.size() - 1;
	}
	else {
		sign = true;
		lenth = s.size();
	}
	lowest_digit = new HP_digit;
	highest_digit = lowest_digit;
	lowest_digit->digit = s[lenth - sign] - 48;

	for (int i = 1; i < lenth; i++) {
		highest_digit->high_digit = new HP_digit;
		highest_digit->high_digit->low_digit = highest_digit;
		highest_digit = highest_digit->high_digit;
		highest_digit->digit = s[lenth - sign - i] - 48;
	}
	hot_digit = lowest_digit;
	del_zeros();
}

void HP_int::operator=(const HP_int& A) {
	free();
	HP_digit* A_hot;

	lenth = A.lenth;
	sign = A.sign;

	lowest_digit = new HP_digit;
	highest_digit = lowest_digit;
	hot_digit = lowest_digit;
	lowest_digit->digit = A.lowest_digit->digit;

	A_hot = A.lowest_digit;
	for (int i = 1; i < lenth; i++) {
		A_hot = A_hot->high_digit;

		highest_digit->high_digit = new HP_digit;
		highest_digit->high_digit->low_digit = highest_digit;
		highest_digit = highest_digit->high_digit;
		highest_digit->digit = A_hot->digit;
	}
}

bool HP_int::operator>(HP_int& A) {
	if (sign != A.sign) {
		return sign;
	}
	else {
		if (lenth > A.lenth) {
			return sign;
		}
		else if (lenth < A.lenth) {
			return !sign;
		}
		else {
			hot_digit = highest_digit;
			A.hot_digit = A.highest_digit;
			if (hot_digit->digit > A.hot_digit->digit) {
				return sign;
			}
			else if (hot_digit->digit < A.hot_digit->digit) {
				return !sign;
			}

			for (int i = 1; i < lenth; i++) {
				hot_digit = hot_digit->low_digit;
				A.hot_digit = A.hot_digit->low_digit;
				if (hot_digit->digit > A.hot_digit->digit) {
					return sign;
				}
				else if (hot_digit->digit < A.hot_digit->digit) {
					return !sign;
				}
			}
			return false;
		}
	}
}

bool HP_int::operator<(HP_int& A) {
	return A > *this;
}

bool HP_int::operator==(HP_int& A) {
	if (lenth != A.lenth || sign != A.sign) {
		return false;
	}
	else {
		hot_digit = highest_digit;
		A.hot_digit = A.highest_digit;
		if (hot_digit->digit != A.hot_digit->digit) {
			return false;
		}
		for (int i = 1; i < lenth; i++) {
			hot_digit = hot_digit->low_digit;
			A.hot_digit = A.hot_digit->low_digit;
			if (hot_digit->digit != A.hot_digit->digit) {
				return false;
			}
		}
		return true;
	}
}

bool HP_int::operator!=(HP_int& A) {
	return !(*this == A);
}

HP_int HP_int::add(HP_int& A) {
	hot_digit = lowest_digit;
	A.hot_digit = A.lowest_digit;
	HP_int result;
	result.sign = true;
	result.lenth = max(A.lenth, lenth);
	result.lowest_digit = new HP_digit;
	result.highest_digit = result.lowest_digit;
	result.hot_digit = result.lowest_digit;
	result.hot_digit->digit = hot_digit->digit + A.hot_digit->digit;

	for (int i = 1; i < result.lenth; i++) {
		result.highest_digit = new HP_digit;
		result.highest_digit->low_digit = result.hot_digit;
		result.hot_digit->high_digit = result.highest_digit;
		result.highest_digit->digit = result.hot_digit->digit / 10;
		result.hot_digit->digit = result.hot_digit->digit % 10;
		result.hot_digit = result.highest_digit;

		if (hot_digit->high_digit != NULL) {
			hot_digit = hot_digit->high_digit;
			result.hot_digit->digit += hot_digit->digit;
		}
		if (A.hot_digit->high_digit != NULL) {
			A.hot_digit = A.hot_digit->high_digit;
			result.hot_digit->digit += A.hot_digit->digit;
		}
	}

	if (result.hot_digit->digit / 10) {
		result.highest_digit = new HP_digit;
		result.highest_digit->low_digit = result.hot_digit;
		result.hot_digit->high_digit = result.highest_digit;
		result.highest_digit->digit = result.hot_digit->digit / 10;
		result.hot_digit->digit = result.hot_digit->digit % 10;
		result.hot_digit = result.highest_digit;
		result.lenth += 1;
	}

	A.hot_digit = A.lowest_digit;
	hot_digit = lowest_digit;
	result.hot_digit = result.lowest_digit;
	return result;
}

HP_int HP_int::minus(HP_int& A) {
	hot_digit = lowest_digit;
	A.hot_digit = A.lowest_digit;
	HP_int result;
	result.sign = true;
	result.lenth = lenth;
	result.lowest_digit = new HP_digit;
	result.highest_digit = result.lowest_digit;
	result.hot_digit = result.lowest_digit;

	unsigned short int borrow = 0;

	result.hot_digit->digit = 10 * !(hot_digit->digit - borrow >= A.hot_digit->digit) + hot_digit->digit - A.hot_digit->digit - borrow;
	borrow = !(hot_digit->digit - borrow >= A.hot_digit->digit);

	for (int i = 1; i < result.lenth; i++) {
		result.highest_digit = new HP_digit;
		result.highest_digit->low_digit = result.hot_digit;
		result.hot_digit->high_digit = result.highest_digit;
		hot_digit = hot_digit->high_digit;
		result.hot_digit = result.highest_digit;

		if (A.hot_digit->high_digit != NULL) {
			A.hot_digit = A.hot_digit->high_digit;
			result.hot_digit->digit = 10 * !(hot_digit->digit - borrow >= A.hot_digit->digit) + hot_digit->digit - A.hot_digit->digit - borrow;
			borrow = !(hot_digit->digit - borrow >= A.hot_digit->digit);
		}
		else {
			result.hot_digit->digit = 10 * !(hot_digit->digit - borrow >= 0) + hot_digit->digit - borrow;
			borrow = !(hot_digit->digit - borrow >= 0);
		}
	}

	result.del_zeros();
	hot_digit = lowest_digit;
	A.hot_digit = A.lowest_digit;
	result.hot_digit = result.lowest_digit;
	return result;
}

HP_int HP_int::decimal(HP_int& A, int num) {
	HP_int ans;
	if (lenth == 1 && lowest_digit->digit == 0) {
		ans = "0";
		ans.lenth = 1;
		while (ans.lenth < num) {
			ans.hot_digit = ans.highest_digit;
			ans.hot_digit->high_digit = new HP_digit;
			ans.highest_digit = ans.hot_digit->high_digit;
			ans.highest_digit->low_digit = ans.hot_digit;
			ans.highest_digit->digit = 0;
			ans.lenth++;
		}
	}
	else {
		for (int i = 0; i < num; i++) {
			hot_digit = lowest_digit;
			hot_digit->low_digit = new HP_digit;
			lowest_digit = hot_digit->low_digit;
			lowest_digit->high_digit = hot_digit;
			lowest_digit->digit = 0;
			lenth++;
		}
		hot_digit = lowest_digit;
		ans = *this / A;
	}
	while (ans.lenth < num) {
		ans.hot_digit = ans.highest_digit;
		ans.hot_digit->high_digit = new HP_digit;
		ans.highest_digit = ans.hot_digit->high_digit;
		ans.highest_digit->low_digit = ans.hot_digit;
		ans.highest_digit->digit = 0;
		ans.lenth++;
	}
	ans.hot_digit = ans.lowest_digit;
	return ans;
}

HP_int HP_int::operator+(HP_int& A) {
	HP_int ans;
	if (sign == A.sign) {
		ans = add(A);
		ans.sign = sign;
	}
	else {
		A.sign = sign;

		bool x = *this > A;
		if (*this == A) {
			ans.lenth = 1;
			ans.lowest_digit = new HP_digit;
			ans.highest_digit = ans.lowest_digit;
			ans.hot_digit = ans.lowest_digit;
			ans.sign = true;
		}
		else if (sign ^ x) {
			ans = A.minus(*this);
			ans.sign = x;
		}
		else {
			ans = minus(A);
			ans.sign = x;
		}
		A.sign = !sign;
	}
	return ans;
}

HP_int HP_int::operator-(HP_int& A) {
	HP_int ans;
	if (sign != A.sign) {
		ans = add(A);
		ans.sign = sign;
	}
	else {
		bool x = *this > A;
		if (*this == A) {
			ans.lenth = 1;
			ans.lowest_digit = new HP_digit;
			ans.highest_digit = ans.lowest_digit;
			ans.hot_digit = ans.lowest_digit;
			ans.sign = true;
		}
		else if (sign ^ x) {
			ans = A.minus(*this);
			ans.sign = x;
		}
		else {
			ans = minus(A);
			ans.sign = x;
		}
	}
	return ans;
}

HP_int HP_int::operator*(HP_int& A) {
	if (lenth < A.lenth) {
		return A * *this;
	}
	else {
		HP_int result;
		result.lowest_digit = new HP_digit;
		result.highest_digit = result.lowest_digit;
		result.hot_digit = result.lowest_digit;
		result.hot_digit->digit = 0;
		result.sign = (sign == A.sign) ? true : false;
		result.lenth = 1;

		HP_digit* hot = result.lowest_digit;
		A.hot_digit = A.lowest_digit;
		for (int i = 0; A.hot_digit != NULL && i < A.lenth; hot = hot->high_digit, A.hot_digit = A.hot_digit->high_digit, i++) {
			hot_digit = lowest_digit;
			result.hot_digit = hot;
			for (int j = 0; hot_digit != NULL && j < lenth; j++, hot_digit = hot_digit->high_digit) {
				result.hot_digit->digit += hot_digit->digit * A.hot_digit->digit;
				if (result.hot_digit->high_digit == NULL) {
					result.highest_digit = new HP_digit;
					result.highest_digit->low_digit = result.hot_digit;
					result.highest_digit->digit = 0;
					result.hot_digit->high_digit = result.highest_digit;
					result.lenth++;
				}
				result.hot_digit = result.hot_digit->high_digit;
				result.hot_digit->digit += result.hot_digit->low_digit->digit / 10;
				result.hot_digit->low_digit->digit = result.hot_digit->low_digit->digit % 10;
			}
		}

		result.del_zeros();
		result.hot_digit = result.lowest_digit;
		hot_digit = lowest_digit;
		A.hot_digit = A.lowest_digit;
		return result;
	}
}

HP_int HP_int::operator/(HP_int& A) {
	HP_int ans;
	HP_int dividend;
	dividend = *this;
	bool A_sign = A.sign;
	dividend.sign = true;
	A.sign = true;

	if (dividend < A) {
		string a = "0";
		ans = a;
	}
	else {
		ans.sign = (sign == A_sign) ? true : false;
		ans.lowest_digit = new HP_digit;
		ans.highest_digit = ans.lowest_digit;
		ans.hot_digit = ans.lowest_digit;
		ans.lenth = lenth - A.lenth + 1;

		for (int j = lenth - A.lenth + 1; j > 0; j--) {
			string q(j, '0');
			q[0] = 9 + 48;
			HP_int quotient;
			quotient = q;
			HP_int dividend_A;
			for (; q[0] - 48 > 0; q[0]--, quotient.highest_digit->digit--) {		//此部分待优化（用减法代替乘法
				dividend_A = quotient * A;
				if (!(dividend_A > dividend)) {
					dividend = dividend - dividend_A;
					break;
				}
			}
			ans.hot_digit->digit = q[0] - 48;
			ans.lowest_digit = new HP_digit;
			ans.hot_digit->low_digit = ans.lowest_digit;
			ans.lowest_digit->high_digit = ans.hot_digit;
			ans.hot_digit = ans.lowest_digit;
		}
		ans.lowest_digit = ans.lowest_digit->high_digit;
		delete ans.hot_digit;
		ans.hot_digit = ans.lowest_digit;
		ans.hot_digit->low_digit = NULL;
	}
	A.sign = A_sign;
	ans.del_zeros();
	return ans;
}

HP_int HP_int::operator%(HP_int& A) {
	HP_int temp;
	HP_int ans;
	temp = *this / A;
	temp = temp * A;
	ans = *this - temp;
	return ans;
}

HP_int HP_int::operator^(HP_int& A) {
	HP_int ans;
	HP_int two;
	two = "2";

	/*/
	HP_int quotient, remainder;

	HP_int this_1, this_2;
	ans = "1";
	this_1 = *this;
	this_2 = this_1;
	while (A.highest_digit->digit > 0) {
		quotient = A / two;
		if (A.lowest_digit->digit % 2 == 1) ans = ans * this_1;
		this_1 = this_1 * this_2;
		this_2 = this_1;
		A = quotient;
	}
	return ans;//*/

	//*
	HP_int quotient, remainder;
	quotient = A / two;
	remainder = two * quotient;
	remainder = A - remainder;

	if (quotient.lenth == 1 && quotient.highest_digit->digit <= 1) {
		if (remainder.lowest_digit->digit % 2 == 0) {
			HP_int this_ = *this;
			ans = this_ * *this;
		}
		else {
			HP_int this_ = *this;
			ans = this_ * *this;
			ans = ans * this_;
		}
	}
	else {
		if (remainder.lowest_digit->digit % 2 == 0) {
			ans = *this ^ quotient;
			HP_int ans_ = ans;
			ans = ans * ans_;
		}
		else {
			ans = *this ^ quotient;
			HP_int ans_ = ans;
			ans = ans * ans_;
			ans = ans * *this;
		}
	}
	return ans;
	//*/
}

HP_int HP_int::factorial()
{	//递归算法中内存不能即时释放，计算上限远低于循环
	//HP_int ans,this_minus1,one;
	//one = "1";
	//if (*this>one) {
	//	this_minus1 = *this - one;
	//	this_minus1 = this_minus1.factorial();
	//	ans = this_minus1 * *this;
	//}
	//else {
	//	return *this;
	//}
	//return ans;

	HP_int ans, one, this_minus;
	one = "1";
	if (*this < one) {
		ans = "1";
		return ans;
	}

	ans = *this;
	this_minus = *this;
	while (this_minus.lenth >= 1 && this_minus.highest_digit->digit > 1) {
		this_minus = this_minus - one;
		ans = ans * this_minus;
	}
	return ans;
}
