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
	void readStr(string var);																//��������
	void in(string real_nume, string real_deno, string imag_nume, string imag_deno);		//��string��ʽ����ʵ�������ķ��ӡ���ĸ���鲿�����ķ��ӷ�ĸ
	void out();																				//�Է�����ʽ���
	string ToString();																		//תΪ�ַ���
	void decimal_out(int num);																//��С����ʽ���
	void free();																			//�ֶ��ͷ�
	void copy_address(HP_complex& A);														//���Ƶ�ַ
	HP_fraction real();																		//��ȡ������ʵ�������ظ߾�����
	HP_fraction imag();																		//��ȡ�������鲿�����ظ߾�����
	void operator=(const HP_complex& A);
	HP_complex operator+(HP_complex& A);
	HP_complex operator-(HP_complex& A);
	HP_complex operator*(HP_complex& A);
	HP_complex operator/(HP_complex& A);
	HP_complex operator^(HP_complex& A);
};