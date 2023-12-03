#pragma once
#include<iostream>
using namespace std;
#include"worker.h"

class manager :public worker
{
public:
	manager(int id, string name, int dID, string gender, string birth, string pstatus, string email);

	virtual void show_info();//显示个人信息

	virtual string get_depname();//获取岗位名称

};