#pragma once
# include <iostream>
# include <string>
using namespace std;

//�߾����ε�һλ
struct HP_digit {
	HP_digit* high_digit;
	HP_digit* low_digit;
	unsigned short int digit;
	HP_digit() { high_digit = NULL; low_digit = NULL; digit = 0; };
};

//һ���߾����Σ��г��ȡ����š����λ�����λ��ַ
class HP_int {
private:
	int lenth;
	HP_digit* highest_digit;
	HP_digit* lowest_digit;
	HP_digit* hot_digit;	//����ʵ�ָ��ֲ�����ָ��
public:
	bool sign;
	HP_int();							//���캯��
	HP_int(const HP_int& A);			//���ƹ��캯��
	HP_int(string A);
	~HP_int();							//��������
	void free();						//�ͷ����е�HP_digit
	void out();							//������������߾�����
	string ToString();					//תΪ�ַ���
	void del_zeros();					//ɾ����λ����
	void copy_address(HP_int& A);		//�����Ƶ�ַ
	int get_lenth();
	void delete_lowdigit(int num);		//���������еĽ�����
	void operator=(string s);			//���ַ���Ϊ�߾����θ�ֵ������ʱ����0����s="123"��С��0����s="-123"��0���ɣ���ֻ����Ϊ+0
	void operator=(const HP_int& A);	//����
	bool operator>(HP_int& A);			//�߾����εıȽϡ��߼����㣬��������
	bool operator<(HP_int& A);
	bool operator==(HP_int& A);
	bool operator!=(HP_int& A);
	HP_int add(HP_int& A);				//add��minusֻʵ����ֵ�ϵļӼ��������Ƿ��ţ�������ɸ߾����ε�+-
	HP_int minus(HP_int& minus);
	HP_int decimal(HP_int& A, int num = 10);	//����С�����֣�numΪ��Ҫ����С����λ��
	HP_int operator+(HP_int& A);		//�߾�����+
	HP_int operator-(HP_int& A);		//�߾�����-
	HP_int operator*(HP_int& A);		//�߾�����*
	HP_int operator/(HP_int& A);		//�߾�����/
	HP_int operator%(HP_int& A);		//�߾�����%
	HP_int operator^(HP_int& A);
	HP_int factorial();
};