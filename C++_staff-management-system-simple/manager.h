#pragma once
#include<iostream>
using namespace std;
#include"worker.h"

class manager :public worker
{
public:
	manager(int id, string name, int dID, string gender, string birth, string pstatus, string email);

	virtual void show_info();//��ʾ������Ϣ

	virtual string get_depname();//��ȡ��λ����

};