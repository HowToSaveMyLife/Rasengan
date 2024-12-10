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
	HP_fraction();								//���ӳ�ʼ��Ϊ0����ĸΪ1
	HP_fraction(const HP_fraction& A);
	HP_fraction(string num);
	HP_fraction(string nume, string deno);
	~HP_fraction();								//��������
	void out();									//�Է�����ʽ���
	void decimal_out(int num = 5);				//��С����ʽ���
	string ToString();							//��������������ַ�����ʽ
	void in(string nume, string denom);			//������string���߾������ķ��ӡ���ĸ��ֵ����ʽͬ�߾�����
	void in(string Num);						//С����ֵ
	void free();								//�ͷ�
	void reduction();							//�Է�������Լ��
	HP_int gcd();								//�����Լ��
	void copy_address(HP_fraction& A);			//���Ƶ�ַ
	void similar(int num);
	void operator=(string num);
	void operator=(const HP_fraction& A);		// = ����һ��
	bool operator>(HP_fraction& A);				//�з����߼�����
	bool operator<(HP_fraction& A);
	bool operator==(HP_fraction& A);
	bool operator!=(HP_fraction& A);


	HP_fraction operator+(HP_fraction& A);		//������������
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