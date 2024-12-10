#pragma once
# include "HP_complex.h"

HP_complex::HP_complex() {
	Real.in("0", "1");
	Imag.in("0", "1");
}

HP_complex::HP_complex(const HP_complex& A) {
	Real = A.Real;
	Imag = A.Imag;
}

HP_complex::HP_complex(string real, string imag) {
	Real.in(real);
	Imag.in(imag);
}

HP_complex::HP_complex(HP_fraction A, HP_fraction B)
{
	this->Real = A;
	this->Imag = B;
}

HP_complex::HP_complex(string real_up, string real_down, string imag_up, string imag_down) {
	Real.in(real_up, real_down);
	Imag.in(imag_up, imag_down);
}

HP_complex::~HP_complex() {
	free();
}

void HP_complex::readStr(string var) {
	int pos, var_lenth;
	string numerator, denominator;
	var_lenth = var.length();

	pos = var.find(',');
	numerator = var.substr(0, pos);
	var = var.substr(pos + 1);

	pos = var.find(',');
	denominator = var.substr(0, pos);
	var = var.substr(pos + 1);

	Real.in(numerator, denominator);

	pos = var.find(',');
	numerator = var.substr(0, pos);
	denominator = var.substr(pos + 1);

	Imag.in(numerator, denominator);
}

void HP_complex::in(string real_nume, string real_deno, string imag_nume, string imag_deno) {
	Real.in(real_nume, real_deno);
	Imag.in(imag_nume, imag_deno);
}

void HP_complex::out() {
	HP_fraction zero;
	zero.in("0");

	if (Real == zero) {
		Imag.out();
		cout << 'j';
	}
	else {
		Real.out();
		if (Imag != zero) {
			if (Imag > zero) cout << '+';
			Imag.out();
			cout << 'j';
		}
	}
}

string HP_complex::ToString() {
	string ans;
	ans = Real.ToString() + ',' + Imag.ToString();
	return ans;
}

void HP_complex::decimal_out(int num) {
	HP_fraction zero;
	zero.in("0");

	if (Real == zero) {
		Imag.decimal_out(num);
		cout << 'j';
	}
	else {
		Real.decimal_out(num);
		if (Imag != zero) {
			if (Imag > zero) cout << '+';
			Imag.decimal_out(num);
			cout << 'j';
		}
	}
}

void HP_complex::free() {
	Real.free();
	Imag.free();
}

void HP_complex::copy_address(HP_complex& A) {
	Real.copy_address(A.Real);
	Imag.copy_address(A.Imag);
}

HP_fraction HP_complex::real() {
	HP_fraction A;
	A = Real;
	return A;
}

HP_fraction HP_complex::imag() {
	HP_fraction A;
	A = Imag;
	return A;
}

void HP_complex::operator=(const HP_complex& A) {
	Real = A.Real;
	Imag = A.Imag;
}

HP_complex HP_complex::operator+(HP_complex& A) {
	HP_complex ans;
	ans.Real = Real + A.Real;
	ans.Imag = Imag + A.Imag;
	return ans;
};

HP_complex HP_complex::operator-(HP_complex& A) {
	HP_complex ans;
	ans.Real = Real - A.Real;
	ans.Imag = Imag - A.Imag;
	return ans;
};

HP_complex HP_complex::operator*(HP_complex& A) {
	HP_complex ans;
	HP_fraction ans_real_1, ans_real_2, ans_imag_1, ans_imag_2;
	ans_real_1 = Real * A.Real;
	ans_real_2 = Imag * A.Imag;
	ans_imag_1 = Real * A.Imag;
	ans_imag_2 = Imag * A.Real;

	ans.Real = ans_real_1 - ans_real_2;
	ans.Imag = ans_imag_1 + ans_imag_2;
	return ans;
};

HP_complex HP_complex::operator/(HP_complex& A) {		//实部等于ac+bd/(c^2+d^2)，虚部等于bc-ad/(c^2+d^2),(a+bj)/(c+dj)
	HP_fraction ac, bd, bc, ad, c_2, d_2, c2_d2;
	HP_complex ans;
	HP_complex T;
	T = A;
	ac = Real * A.Real;
	bd = Imag * A.Imag;
	bc = Imag * A.Real;
	ad = Real * A.Imag;
	c_2 = A.Real * T.Real;
	d_2 = A.Imag * T.Imag;
	c2_d2 = c_2 + d_2;
	ans.Real = ac + bd;
	ans.Real = ans.Real / c2_d2;
	ans.Imag = bc - ad;
	ans.Imag = ans.Imag / c2_d2;
	return ans;
}

HP_complex HP_complex::operator^(HP_complex& A) {
	HP_complex ans;
	ans.Real = Real ^ A.Real;
	ans.Imag.in("0");
	return ans;
}