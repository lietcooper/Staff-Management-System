#pragma once//防止头文件重复包含
#include<iostream>
using namespace std; //使用标准命名空间
#include"worker.h"
#include"employee.h"
#include"boss.h"
#include"manager.h"
#include<fstream>
#include<stdlib.h>
#define FILENAME "empFile.txt"



class workerManager
{
public:

	workerManager();//构造函数

	//展示菜单
	void show_menu();

	//退出系统
	void exitsystem();

	~workerManager();//析构函数
	
	//记录职工人数
	int m_EmpNum;

	//职工的指针数组的指针
	worker** m_EmpArray;

	//添加职工
	void addEmp();

	//保存文件
	void save();

	//判断文件是否为空
	bool m_FileIsEmpty;

	//统计文件中人数
	int get_EmpNum();

	//初始化员工
	void init_Emp();

	//显示员工
	void show_Emp();

	//删除职工
	void Del_Emp();

	//判断存在
	int IsExist(int id);

	//修改职工
	void Mod_Emp();

	//查找职工
	void Find_Emp();

	//按职工编号排序
	void sort_Emp();

	//清空数据
	void clean_file();
};