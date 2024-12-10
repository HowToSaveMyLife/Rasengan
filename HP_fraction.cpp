#pragma once
# include "HP_fraction.h"

HP_fraction ln2("0.69314718055994528622676398299518041312694549560546875");
HP_fraction e[] = {
	HP_fraction("6235149080811616882909238708.92846974483139184623579991438859169901398477628683"),
	HP_fraction("78962960182680.69516097802263510822421995619511535233065508002059"),
	HP_fraction("8886110.52050787263676302374078145035080271982185663883978"),
	HP_fraction("2980.95798704172827474359209945288867375596793913283570"),
	HP_fraction("54.59815003314423907811026120286087840279073703861406"),
	HP_fraction("7.38905609893065022723042746057500781318031557055184"),
	HP_fraction("2.71828182845904523536028747135266249775724709369995"),
};

HP_fraction::HP_fraction() {
	numerator = "0";
	denominator = "1";
}

HP_fraction::HP_fraction(const HP_fraction& A) {
	numerator = A.numerator;
	denominator = A.denominator;
}

HP_fraction::HP_fraction(string num) {
	in(num);
}

HP_fraction::HP_fraction(string nume, string deno) {
	in(nume, deno);
}

HP_fraction::~HP_fraction() {
	free();
}

void HP_fraction::out() {
	HP_int zero, one;
	zero = "0";
	one = "1";
	if (numerator == zero) {
		numerator.out();
	}
	else {
		if (denominator == one) {
			numerator.out();
		}
		else {
			numerator.out();
			cout << '/';
			denominator.out();
		}
	}
}

void HP_fraction::decimal_out(int num) {
	HP_int zero;
	zero = "0";

	if (numerator == zero) {
		cout << '0';
	}
	else {
		HP_int quotient;
		quotient = numerator / denominator;
		quotient.sign = numerator.sign;
		quotient.out();
		cout << '.';
		HP_int remainder;
		remainder = denominator * quotient;
		remainder = numerator - remainder;
		remainder.sign = denominator.sign;
		quotient = remainder.decimal(denominator, num);
		quotient.out();
	}
}

string HP_fraction::ToString()
{
	string ans;
	ans = numerator.ToString() + ',' + denominator.ToString();
	return ans;
}

void HP_fraction::in(string nume, string denom) {
	numerator = nume;
	denominator = denom;
	reduction();
}

void HP_fraction::in(string Num) {
	int pos = Num.find('.');
	if (pos == -1) in(Num, "1");
	else {
		int Num_lenth = Num.length();
		int Deno_lenth;
		string Nume, Deno;
		Nume = Num.substr(0, pos) + Num.substr(pos + 1, Num_lenth);
		Deno_lenth = Num_lenth - pos - 1;
		Deno = "1" + string(Deno_lenth, '0');
		in(Nume, Deno);
	}
}

void HP_fraction::free() {
	numerator.free();
	denominator.free();
}

void HP_fraction::reduction() {
	HP_int temp;
	bool sign;
	temp = "0";
	if (numerator == temp) {
		denominator = "1";
		return;
	}

	if (numerator.sign == denominator.sign) sign = true;
	else sign = false;

	temp = gcd();
	denominator = denominator / temp;
	numerator = numerator / temp;
	numerator.sign = sign;
	denominator.sign = true;
}

HP_int HP_fraction::gcd() {			//最大公约数仅正数
	HP_int a, b, temp, zero;
	zero = "0";
	a = numerator;
	a.sign = true;
	b = denominator;
	b.sign = true;
	temp = a % b;
	while (temp != zero) {
		a = b;
		b = temp;
		temp = a % b;
	}
	return b;
}

void HP_fraction::copy_address(HP_fraction& A) {
	numerator.copy_address(A.numerator);
	denominator.copy_address(A.denominator);
}

void HP_fraction::similar(int num) {
	int nume_lenth = numerator.get_lenth();
	int deno_lenth = denominator.get_lenth();
	int lenth_minus = nume_lenth - deno_lenth;
	if (lenth_minus <= 0) {
		numerator.delete_lowdigit(nume_lenth - num - 1);
		denominator.delete_lowdigit(deno_lenth - num - 1);
	}
	else {
		numerator.delete_lowdigit(deno_lenth - num - lenth_minus - 1);
		denominator.delete_lowdigit(deno_lenth - num - lenth_minus - 1);
	}
}

void HP_fraction::operator=(string num){
	in(num);
}

void HP_fraction::operator=(const HP_fraction& A) {
	numerator = A.numerator;
	denominator = A.denominator;
	reduction();
}

bool HP_fraction::operator>(HP_fraction& A) {
	HP_int a, b;
	bool ans;
	a = numerator * A.denominator;
	b = denominator * A.numerator;
	if (a > b) ans = true;
	else ans = false;
	return ans;
}

bool HP_fraction::operator<(HP_fraction& A) {
	return A > *this;
}

bool HP_fraction::operator==(HP_fraction& A) {
	HP_int a, b;
	bool ans;
	a = numerator * A.denominator;
	b = denominator * A.numerator;
	if (a == b) ans = true;
	else ans = false;
	return ans;
}

bool HP_fraction::operator!=(HP_fraction& A) {
	return !(*this == A);
}

HP_fraction HP_fraction::operator+(HP_fraction& A) {
	HP_fraction ans;
	ans.denominator = A.denominator * denominator;
	HP_int numerator_1, numerator_2;
	numerator_1 = numerator * A.denominator;
	numerator_2 = A.numerator * denominator;
	ans.numerator = numerator_1 + numerator_2;
	ans.reduction();
	return ans;
}

HP_fraction HP_fraction::operator-(HP_fraction& A) {
	HP_fraction ans;
	ans.denominator = A.denominator * denominator;
	HP_int numerator_1, numerator_2;
	numerator_1 = numerator * A.denominator;
	numerator_2 = A.numerator * denominator;
	ans.numerator = numerator_1 - numerator_2;
	ans.reduction();
	return ans;
}

//乘除待优化，先约分，再乘除

HP_fraction HP_fraction::operator*(HP_fraction& A) {
	HP_fraction ans;
	ans.denominator = A.denominator * denominator;
	ans.numerator = numerator * A.numerator;
	ans.reduction();
	return ans;
}

HP_fraction HP_fraction::operator/(HP_fraction& A) {
	HP_fraction ans;
	ans.denominator = A.numerator * denominator;
	ans.numerator = numerator * A.denominator;
	ans.reduction();
	return ans;
}

HP_fraction HP_fraction::operator^(HP_fraction& A) {
	HP_fraction ans;
	ans.numerator = numerator ^ A.numerator;
	ans.denominator = denominator ^ A.numerator;
	if (!A.numerator.sign) {
		HP_fraction one;
		one.in("1");
		return one / ans;
	}
	return ans;
}

HP_fraction HP_fraction::exp(int num) {
	int x[7] = { 0 };
	HP_fraction k("64"), two("2");
	HP_fraction ans = *this;
	for (int i = 0; i < 7; i++) {
		while (!(ans < k)) {
			ans = ans - k;
			x[i]++;
		}
		k = k / two;
	}
	ans = ans.exp_base(num+5);

	for (int i = 0; i < 7; i++) {
		for (; x[i] > 0; x[i]--) ans = ans * e[i];
	}
	return ans;
}

HP_fraction HP_fraction::exp_base(int num) {
	HP_fraction ans;
	HP_fraction k("1"), middle_var("1"), deno("1"), one("1");
	ans = middle_var;
	HP_fraction Error("1", '1' + string(num + 1, '0'));
	middle_var = middle_var * *this;
	while (middle_var > Error) {
		
		ans = ans + middle_var;
		k = k + one;
		middle_var = middle_var * *this;
		middle_var = middle_var / k;
		
		int ans_lenth = ans.denominator.get_lenth(), middle_var_lenth = middle_var.numerator.get_lenth();
		if (ans_lenth > 1000) ans.similar(1000);
		if (middle_var_lenth > 100) middle_var.similar(1000);
	}
	return ans;
}

//求自然底数的对数
HP_fraction HP_fraction::ln(int num) {
	HP_fraction ans = *this, two("2"), middle_var, one("1");
	int k = 0;
	while (ans > two || ans == two) {
		ans = ans / two;
		k++;
	}
	ans = ans.ln_base(num);
	string x = to_string(k);
	middle_var = x;
	middle_var = middle_var * ln2;
	ans = ans + middle_var;
	return ans;
}

HP_fraction HP_fraction::ln_base(int num) {
	HP_fraction ans, y, middle_var, one, Error, two, nume, deno;
	string error(num + 2, '0');
	error[0] = 1;
	Error.in("1", error);
	one.in("1");
	two.in("2");
	y = *this - one;
	middle_var = *this + one;
	y = y / middle_var;

	ans = two * y;
	y = y ^ two;
	nume = ans * y;
	deno = one + two;
	middle_var = nume / deno;
	while (middle_var > Error) {
		ans = ans + middle_var;

		nume = nume * y;
		deno = deno + two;
		middle_var = nume / deno;
	}

	return ans;
}

//算法优化
//预处理，将数字放缩到0至100间，然后开方
HP_fraction HP_fraction::sqrt(int num) {
	HP_fraction ans, one,ten, hundred;
	one.in("1");
	ten.in("10");
	hundred.in("100");
	int zero_num = 0;
	ans = *this;
	while (ans > hundred) {
		ans = ans / hundred;
		zero_num++;
	}
	ans = ans.sqrt_base(num + zero_num);
	for (int i = 0; i < zero_num; i++) {
		ans = ans * ten;
	}
	return ans;
}

//牛顿下山法
HP_fraction HP_fraction::sqrt_base(int num) {
	HP_fraction ans, two, Error;
	string error(num + 2, '0');
	error[0] = '1';
	two.in("2");
	ans = *this;
	Error.in("1", error);

	HP_fraction ans_2, middle_var;
	ans_2 = ans ^ two;
	while (ans_2 > *this) {
		middle_var = *this / ans;
		middle_var = ans + middle_var;
		ans = middle_var / two;
		ans.similar(num);
		ans_2 = ans - Error;
		ans_2 = ans_2 ^ two;
	}
	return ans;
}

HP_fraction HP_fraction::factorial()
{
	HP_fraction ans;
	ans.numerator = numerator.factorial();
	ans.denominator = denominator.factorial();
	return ans;
}

HP_fraction log(HP_fraction& A, HP_fraction& M) {
	HP_fraction ans, ans1, ans2;
	ans1 = A.ln();
	ans2 = M.ln();
	ans = ans1 - ans2;
	return ans;
}