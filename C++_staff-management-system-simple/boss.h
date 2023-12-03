#pragma once
#include<iostream>
using namespace std;
#include"worker.h"

class boss :public worker
{
public:
	boss(int id, string name, int dID, string gender, string birth, string pstatus, string email);

	virtual void show_info();

	virtual string get_depname();
};