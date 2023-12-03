#pragma once
#include<iostream>
using namespace std;
#include<string>

class worker
{
public:

	virtual void show_info() = 0;//显示个人信息

	virtual string get_depname() = 0;//获取岗位名称

	int m_ID;
	string m_name;
	int m_depID;
	string m_gender;
	string m_birth;
	string m_pstatus;
	string m_email;
};
